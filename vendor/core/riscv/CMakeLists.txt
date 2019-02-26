## Andes
option (USE_ANDES "USE ANDES Core." ON)
if (USE_ANDES)
        add_subdirectory (andes)
endif (USE_ANDES)

## SiFive
option (USE_SIFIVE "USE SIFIVE Core." ON)
if (USE_SIFIVE)
        add_subdirectory (sifive)
endif (USE_SIFIVE)
