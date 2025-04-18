#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#build_yet is a boolean variable that is used in the CMakelists.txt of umock_c_2_int.
#it is used to prohibit generating more than 1 times the project umock_c_2_mock_pp which is intended to be generated only once.
set(build_yet FALSE)

#unit tests
if(${run_unittests})
    build_test_folder(umockalloc_ut)
    build_test_folder(umockstring_ut)
    build_test_folder(umockautoignoreargs_ut)
    build_test_folder(umockcall_ut)
    build_test_folder(umockcallpairs_ut)
    build_test_folder(umockcallrecorder_ut)
    build_test_folder(umock_c_ut)
    build_test_folder(umock_c_wout_init_ut)
    build_test_folder(umocktypename_ut)
    build_test_folder(umocktypes_ut)
    build_test_folder(umocktypes_c_fixed_buffer_ut)
    build_test_folder(umocktypes_wout_init_ut)
    build_test_folder(umocktypes_bool_ut)
    build_test_folder(umocktypes_c_ut)
    build_test_folder(umocktypes_charptr_ut)
    build_test_folder(umocktypes_stdint_ut)
    build_test_folder(umocktypes_wcharptr_ut)
    build_test_folder(umock_c_negt_noini_ut)
    build_test_folder(umock_c_negt_ut)

    if(WIN32)
        build_test_folder(umock_lock_factory_windows_ut)
        build_test_folder(umocktypes_windows_ut)
    endif()
    if(UNIX)
        build_test_folder(umock_lock_factory_pthread_ut)
    endif()
endif()

#int tests
if(${run_int_tests})
    build_test_folder(umock_c_int)
    build_test_folder(umock_c_reals_int)
    build_test_folder(umock_c_mock_filters_int)
    build_test_folder(umock_c_negt_int)
    build_test_folder(umock_c_gen_func_decl_int)
    build_test_folder(umock_c_malloc_hook_int)
    build_test_folder(umock_c_ptrarg_leak_int)
    build_test_folder(umocktypes_struct_int)
    if((WIN32) OR (UNIX))
        build_test_folder(umock_c_with_lock_factory_int)
    endif()

    if(WIN32)
        build_test_folder(umock_c_windows_types_int)
        build_test_folder(umock_c_reg_win_types_int)
    endif()
endif()