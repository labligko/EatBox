cmake_minimum_required(VERSION 4.0)
project(perapihan C)

set(CMAKE_C_STANDARD 23)

add_executable(perapihan main.c
        include/data.h
        src/function.c
        include/function.h
        src/login.c
        include/login.h
        src/master/karyawan/superadmin.c
        src/master/karyawan/kasir.c
        src/master/karyawan/staff.c
        src/master/karyawan/manajer.c
        include/master/karyawan/kasir.h
        include/master/karyawan/manajer.h
        include/master/karyawan/staff.h
        include/master/karyawan/superadmin.h
        include/transaksi/pembayaran.h
        include/transaksi/pesanan.h
        src/transaksi/pembayaran.c
        src/transaksi/pesanan.c
        include/master/meja.h
        include/master/menu.h
        include/master/bahanBaku.h
        include/master/resep.h
        src/master/meja.c
        src/master/menu.c
        src/master/resep.c
        src/master/bahanBaku.c)
