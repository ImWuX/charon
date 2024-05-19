#include "gen.h"

LLVMTypeRef gen_llvm_type(gen_context_t *ctx, ir_type_t *type) {
    if(ir_type_is_kind(type, IR_TYPE_KIND_VOID)) return ctx->types.void_;
    if(ir_type_is_kind(type, IR_TYPE_KIND_POINTER)) return ctx->types.pointer;
    if(ir_type_is_kind(type, IR_TYPE_KIND_INTEGER)) {
        switch(type->integer.bit_size) {
            case 1: return ctx->types.int1;
            case 8: return ctx->types.int8;
            case 16: return ctx->types.int16;
            case 32: return ctx->types.int32;
            case 64: return ctx->types.int64;
        }
    }
    assert(false);
}

static void gen_program(gen_context_t *ctx, ir_node_t *node) {
    for(size_t i = 0; i < node->program.global_count; i++) gen_global(ctx, node->program.globals[i]);
}

void gen(ir_node_t *ast, const char *dest, const char *passes) {
    gen_context_t ctx = {};
    ctx.context = LLVMContextCreate();
    ctx.module = LLVMModuleCreateWithNameInContext("CharonModule", ctx.context);
    ctx.builder = LLVMCreateBuilderInContext(ctx.context);

    ctx.types.void_ = LLVMVoidTypeInContext(ctx.context);
    ctx.types.pointer = LLVMPointerTypeInContext(ctx.context, 0);
    ctx.types.int1 = LLVMInt1TypeInContext(ctx.context);
    ctx.types.int8 = LLVMInt8TypeInContext(ctx.context);
    ctx.types.int16 = LLVMInt16TypeInContext(ctx.context);
    ctx.types.int32 = LLVMInt32TypeInContext(ctx.context);
    ctx.types.int64 = LLVMInt64TypeInContext(ctx.context);
    ctx.scope = NULL;

    gen_program(&ctx, ast);

    LLVMRunPasses(ctx.module, passes, NULL, LLVMCreatePassBuilderOptions());
    LLVMPrintModuleToFile(ctx.module, dest, NULL);

    // Cleanup
    LLVMDisposeBuilder(ctx.builder);
    LLVMDisposeModule(ctx.module);
    LLVMContextDispose(ctx.context);
}