// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCKTYPES_H
#define UMOCKTYPES_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdio>
#else
#include <stddef.h>
#include <stdio.h>
#endif

#include "macro_utils/macro_utils.h"

#include "umock_c/umock_c.h"
#include "umock_c/umockalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef char*(*UMOCKTYPE_STRINGIFY_FUNC)(const void* value);
    typedef int(*UMOCKTYPE_COPY_FUNC)(void* destination, const void* source);
    typedef void(*UMOCKTYPE_FREE_FUNC)(void* value);
    typedef int(*UMOCKTYPE_ARE_EQUAL_FUNC)(const void* left, const void* right);

    int umocktypes_init(void);
    void umocktypes_deinit(void);
    int umocktypes_register_type(const char* type, UMOCKTYPE_STRINGIFY_FUNC stringify_func, UMOCKTYPE_ARE_EQUAL_FUNC are_equal_func, UMOCKTYPE_COPY_FUNC copy_func, UMOCKTYPE_FREE_FUNC free_func);
    int umocktypes_register_alias_type(const char* type, const char* alias_type);

    char* umocktypes_stringify(const char* type, const void* value);
    int umocktypes_are_equal(const char* type, const void* left, const void* right);
    int umocktypes_copy(const char* type, void* destination, const void* source);
    void umocktypes_free(const char* type, void* value);

    /* This is a convenience macro that allows registering a type by simply specifying the name and a function_postfix*/
#define REGISTER_TYPE(type, function_postfix) \
        umocktypes_register_type(MU_TOSTRING(type), (UMOCKTYPE_STRINGIFY_FUNC)MU_C2(umocktypes_stringify_, function_postfix), \
            (UMOCKTYPE_ARE_EQUAL_FUNC)MU_C2(umocktypes_are_equal_,function_postfix), \
            (UMOCKTYPE_COPY_FUNC)MU_C2(umocktypes_copy_,function_postfix), \
            (UMOCKTYPE_FREE_FUNC)MU_C2(umocktypes_free_,function_postfix))

#define IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_COMMON(enum_name, ...) \
    char* MU_C2(umocktypes_stringify_,enum_name)(const enum_name* value) \
    { \
        char* result; \
        if (value == NULL) \
        { \
            result = NULL; \
        } \
        else \
        { \
            int length = snprintf(NULL, 0, "%" PRI_MU_ENUM "", MU_ENUM_VALUE(MU_C2(enum_name,_for_umock), *value)); \
            if (length < 0) \
            { \
                result = NULL; \
            } \
            else \
            { \
                result = (char*)umockalloc_malloc(length + 1); \
                if (result != NULL) \
                { \
                    if (snprintf(result, length + 1, "%" PRI_MU_ENUM "", MU_ENUM_VALUE(MU_C2(enum_name,_for_umock), *value)) < 0) \
                    { \
                        umockalloc_free(result); \
                    } \
                    else \
                    { \
                        /* return as is */ \
                    } \
                } \
                else \
                { \
                    /* return as is */ \
                } \
            } \
        } \
        return result; \
    }
/* Codes_SRS_UMOCK_C_LIB_01_181: [ If a value that is not part of the enum is used, it shall be treated as an int value. ]*/
#define IMPLEMENT_UMOCK_C_ENUM_STRINGIFY(enum_name, ...) \
    typedef enum_name MU_C2(enum_name,_for_umock); \
    MU_DEFINE_ENUM_STRINGS(MU_C2(enum_name,_for_umock), __VA_ARGS__); \
    IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_COMMON(enum_name, __VA_ARGS__)

#define IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_WITHOUT_INVALID(enum_name, ...) \
    typedef enum_name MU_C2(enum_name,_for_umock); \
    MU_DEFINE_ENUM_STRINGS_WITHOUT_INVALID(MU_C2(enum_name,_for_umock), __VA_ARGS__); \
    IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_COMMON(enum_name, __VA_ARGS__)

#define IMPLEMENT_UMOCK_C_ENUM_ARE_EQUAL(type) \
    int MU_C2(umocktypes_are_equal_,type)(const type* left, const type* right) \
    { \
        int result; \
        if ((left == NULL) || (right == NULL)) \
        { \
            result = -1; \
        } \
        else \
        { \
            result = ((*left) == (*right)) ? 1 : 0; \
        } \
        return result; \
    }

#define IMPLEMENT_UMOCK_C_ENUM_COPY(type) \
    int MU_C2(umocktypes_copy_,type)(type* destination, const type* source) \
    { \
        int result; \
        if ((destination == NULL) || \
            (source == NULL)) \
        { \
            result = __LINE__; \
        } \
        else \
        { \
            *destination = *source; \
            result = 0; \
        } \
        return result; \
    }

#define IMPLEMENT_UMOCK_C_ENUM_FREE(type) \
    void MU_C2(umocktypes_free_,type)(type* value) \
    { \
        (void)value; \
    }

/* Codes_SRS_UMOCK_C_LIB_01_179: [ IMPLEMENT_UMOCK_C_ENUM_TYPE and IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_WITHOUT_INVALID shall implement umock_c handlers for an enum type. ]*/
/* Codes_SRS_UMOCK_C_LIB_01_180: [ The variable arguments are a list making up the enum values. ]*/
#define IMPLEMENT_UMOCK_C_ENUM_TYPE(type, ...) \
    IMPLEMENT_UMOCK_C_ENUM_STRINGIFY(type, __VA_ARGS__) \
    IMPLEMENT_UMOCK_C_ENUM_ARE_EQUAL(type) \
    IMPLEMENT_UMOCK_C_ENUM_COPY(type) \
    IMPLEMENT_UMOCK_C_ENUM_FREE(type)

#define IMPLEMENT_UMOCK_C_ENUM_TYPE_WITHOUT_INVALID(type, ...) \
    IMPLEMENT_UMOCK_C_ENUM_STRINGIFY_WITHOUT_INVALID(type, __VA_ARGS__) \
    IMPLEMENT_UMOCK_C_ENUM_ARE_EQUAL(type) \
    IMPLEMENT_UMOCK_C_ENUM_COPY(type) \
    IMPLEMENT_UMOCK_C_ENUM_FREE(type)

#ifdef __cplusplus
}
#endif

#endif /* UMOCKTYPES_H */
