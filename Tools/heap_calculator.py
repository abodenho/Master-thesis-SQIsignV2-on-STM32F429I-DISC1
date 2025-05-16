COMPUTE_RAM = True
FINAL_HP = 0x200A0000   #TODO modifie


INITIAL_HP_RAM =   0x20042140
INITIAL_HP_SDRAM = 0xd0000000

if COMPUTE_RAM:
    INITIAL_HP = INITIAL_HP_RAM
else:
    INITIAL_HP = INITIAL_HP_SDRAM



response = abs(FINAL_HP - INITIAL_HP)  # size in bytes
response = int(response) / 1024 # conversion to KB
print(str(response) + " KB")
response = int(response) / 1024 # conversion to MB
print(str(response) + " MB")

