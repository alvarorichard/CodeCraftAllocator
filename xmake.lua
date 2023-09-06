-- xmake.lua
add_rules("mode.debug", "mode.release")

target("malloc")
    set_kind("shared")
    add_files("src/main.c")  -- Especifique o caminho completo do arquivo main.c
    set_toolchains("clang")  -- Usar o Clang como compilador
    add_cxflags("-O0", "-g", "-W", "-Wall", "-Wextra")
    add_ldflags("-shared", "-fPIC")
