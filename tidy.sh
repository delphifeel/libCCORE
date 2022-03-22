CHECKS="*,-llvm-include-order,-llvm-header-guard,-misc-unused-parameters"
SRC_FILES="src/*"

clang-tidy-8                                            \
    -checks=$CHECKS                                     \
    -header-filter=.*                                   \
    $SRC_FILES --                                       \
    -I include                                    
