gpi_path = "MDMF_" # Тут меняем FIOF_ на своё

# = = = = = = = = = = = = = = = =

print(" %-32s %32s" % ("=Галанин П. И.=", "=gpi_autorename="))

import os
for root, dirs, files in os.walk("."):  
    for gpi_filename in files:
        gpi_s = gpi_filename
        gpi_s = gpi_s.replace("FIOF_", gpi_path)
        os.rename(gpi_filename, gpi_s)
        print(" gpi_autorename Rename: %s => %s" % (gpi_filename, gpi_s))
