import serial
import re
import pandas as pd
from time import sleep
from pathlib import Path

PORT = 'COM4'  
BAUD_RATE = 115200
EXCEL_PATH = 'SQIsign_level1.xlsx'

phase_pattern = re.compile(r"^(KEY GENERATION|SIGN|VERIFICATION)$", re.IGNORECASE)
time_pattern = re.compile(r"TIME\s*:\s*(\d+)\s*ms", re.IGNORECASE)
cycle_pattern = re.compile(r"NUMBER CYCLE\s*:\s*(\d+)\s*cycles", re.IGNORECASE)
stack_pattern = re.compile(r"STACK USED\s*:\s*(\d+)\s*bytes", re.IGNORECASE)
final_heap_pattern = re.compile(r"HEAP USAGE\s*:\s*(\d+)\s*bytes", re.IGNORECASE)

phases = ['KEY GENERATION', 'SIGN', 'VERIFICATION']
measurements = {p: {} for p in phases}
current_phase = None
heap_total = None

if Path(EXCEL_PATH).exists():
    df = pd.read_excel(EXCEL_PATH)
else:
    columns = ['#']
    for phase in phases:
        columns += [f'{phase} {x}' for x in ['ms', 's', 'm', 'cycles', 'Mc', 'stack_B', 'stack_kB', 'stack_MB']]
    columns += [f'Total {x}' for x in ['ms', 's', 'm', 'cycles', 'Mc']]
    columns += ['heap_B', 'heap_kB', 'heap_MB']
    df = pd.DataFrame(columns=columns)

def convert_metrics(ms, cycles, stack_b):
    s = ms / 1000
    m = s / 60
    Mc = cycles / 1_000_000
    stack_kB = stack_b / 1024
    stack_MB = stack_b / 1_048_576
    return [ms, round(s, 5), round(m, 5), cycles, round(Mc, 5),
            stack_b, round(stack_kB, 5), round(stack_MB, 5)]

def append_to_excel(df, measurements, heap_total):
    new_index = int(df.iloc[-1, 0]) + 1 if not df.empty else 1
    row = [new_index]
    total_ms = total_cycles = 0

    for phase in phases:
        m = measurements[phase]
        row.extend(convert_metrics(m['ms'], m['cycles'], m['stack']))
        total_ms += m['ms']
        total_cycles += m['cycles']

    total_s = total_ms / 1000
    total_m = total_s / 60
    total_Mc = total_cycles / 1_000_000
    row.extend([total_ms, round(total_s, 6), round(total_m, 6), total_cycles, round(total_Mc, 3)])

    if heap_total is not None:
        heap_kB = heap_total / 1024
        heap_MB = heap_total / 1_048_576
        row.extend([heap_total, round(heap_kB, 5), round(heap_MB, 5)])
    else:
        row.extend([None, None, None])

    df.loc[len(df)] = row
    df.to_excel(EXCEL_PATH, index=False)
    print("===========================================================")

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    while True:
        if ser.in_waiting:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            print(">>", line)

            if "DEAD" in line:
                if all(all(k in m for k in ['ms', 'cycles', 'stack']) for m in measurements.values()) and heap_total is not None:
                    append_to_excel(df, measurements, heap_total)
                break

            if "START" in line.upper():
                if all(all(k in m for k in ['ms', 'cycles', 'stack']) for m in measurements.values()) and heap_total is not None:
                    append_to_excel(df, measurements, heap_total)
                measurements = {p: {} for p in phases}
                current_phase = None
                heap_total = None
                continue

            if final_heap_pattern.search(line):
                heap_total = int(final_heap_pattern.search(line).group(1))
                print(f"Final heap usage captured: {heap_total} bytes")
                continue

            match = phase_pattern.match(line)
            if match:
                current_phase = match.group(1).upper()
                continue

            if current_phase:
                if time_pattern.search(line):
                    measurements[current_phase]['ms'] = int(time_pattern.search(line).group(1))
                elif cycle_pattern.search(line):
                    measurements[current_phase]['cycles'] = int(cycle_pattern.search(line).group(1))
                elif stack_pattern.search(line):
                    measurements[current_phase]['stack'] = int(stack_pattern.search(line).group(1))

                if all(k in measurements[current_phase] for k in ['ms', 'cycles', 'stack']):
                    current_phase = None

        sleep(0.1)

except KeyboardInterrupt:
    print("Stop")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
