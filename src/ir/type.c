#include "type.h"
#include <stdlib.h>
#include <stdio.h>

static ir_type_t *g_void = NULL, *g_u8 = NULL, *g_u16 = NULL, *g_u32 = NULL, *g_u64 = NULL;

static ir_type_t *make_type(ir_type_kind_t kind) {
    ir_type_t *type = malloc(sizeof(ir_type_t));
    type->kind = kind;
    return type;
}

bool ir_type_is_kind(ir_type_t *type, ir_type_kind_t kind) {
    return type->kind == kind;
}

bool ir_type_is_void(ir_type_t *type) {
    return ir_type_is_kind(type, TYPE_KIND_VOID);
}

bool ir_type_is_eq(ir_type_t *a, ir_type_t *b) {
    if(a->kind != b->kind) return false;
    switch(a->kind) {
        case TYPE_KIND_VOID: return true;
        case TYPE_KIND_UNSIGNED_INTEGER: return a->integer.bit_size == b->integer.bit_size;
        case TYPE_KIND_POINTER: return ir_type_is_eq(a->pointer.base, b->pointer.base);
    }
}

ir_type_t *ir_type_get_void() {
    if(g_void == NULL) g_void = make_type(TYPE_KIND_VOID);
    return g_void;
}

ir_type_t *ir_type_get_u8() {
    if(g_u8 == NULL) g_u8 = make_type(TYPE_KIND_UNSIGNED_INTEGER);
    g_u8->integer.bit_size = 8;
    return g_u8;
}

ir_type_t *ir_type_get_u16() {
    if(g_u16 == NULL) g_u16 = make_type(TYPE_KIND_UNSIGNED_INTEGER);
    g_u16->integer.bit_size = 16;
    return g_u16;
}

ir_type_t *ir_type_get_u32() {
    if(g_u32 == NULL) g_u32 = make_type(TYPE_KIND_UNSIGNED_INTEGER);
    g_u32->integer.bit_size = 32;
    return g_u32;
}

ir_type_t *ir_type_get_u64() {
    if(g_u64 == NULL) g_u64 = make_type(TYPE_KIND_UNSIGNED_INTEGER);
    g_u64->integer.bit_size = 64;
    return g_u64;
}

ir_type_t *ir_type_get_uint() {
    return ir_type_get_u64();
}

ir_type_t *ir_type_make_pointer(ir_type_t *base) {
    ir_type_t *type = make_type(TYPE_KIND_POINTER);
    type->pointer.base = base;
    return type;
}