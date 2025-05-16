COMPUTE_RAM = True #TODO modifie
FINAL_SP = 0x2000e268 #TODO modifie

INITIAL_SP_RAM = 0x200A0000
INITIAL_SP_SDRAM = 0xd0800000

if COMPUTE_RAM:
    INITAL_SP = INITIAL_SP_RAM
else:
    INITAL_SP = INITIAL_SP_SDRAM


response = abs(FINAL_SP - INITAL_SP)  # size in bytes
response = int(response) / 1024 # conversion to KB
print(str(response) + " KB")
response = int(response) / 1024 # conversion to MB
print(str(response) + " MB")



