#include "node.h"
#include <stdlib.h>

static ir_node_t *make_node(ir_node_type_t type, diag_loc_t diag_loc) {
    ir_node_t *node = malloc(sizeof(ir_node_t));
    node->type = type;
    node->diag_loc = diag_loc;
    return node;
}

ir_node_t *ir_node_make_program(size_t global_count, ir_node_t **globals, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_PROGRAM, diag_loc);
    node->program.global_count = global_count;
    node->program.globals = globals;
    return node;
}

ir_node_t *ir_node_make_global_function(ir_function_decl_t function_decl, ir_node_t *body, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_GLOBAL_FUNCTION, diag_loc);
    node->global_function.decl = function_decl;
    node->global_function.body = body;
    return node;
}

ir_node_t *ir_node_make_global_extern(ir_function_decl_t function_decl, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_GLOBAL_EXTERN, diag_loc);
    node->global_extern.decl = function_decl;
    return node;
}

ir_node_t *ir_node_make_expr_literal_numeric(uintmax_t value, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_LITERAL_NUMERIC, diag_loc);
    node->expr_literal.numeric_value = value;
    return node;
}

ir_node_t *ir_node_make_expr_literal_string(const char *value, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_LITERAL_STRING, diag_loc);
    node->expr_literal.string_value = value;
    return node;
}

ir_node_t *ir_node_make_expr_literal_char(char value, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_LITERAL_CHAR, diag_loc);
    node->expr_literal.char_value = value;
    return node;
}

ir_node_t *ir_node_make_expr_literal_bool(bool value, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_LITERAL_BOOL, diag_loc);
    node->expr_literal.bool_value = value;
    return node;
}

ir_node_t *ir_node_make_expr_binary(ir_binary_operation_t operation, ir_node_t *left, ir_node_t *right, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_BINARY, diag_loc);
    node->expr_binary.operation = operation;
    node->expr_binary.left = left;
    node->expr_binary.right = right;
    return node;
}

ir_node_t *ir_node_make_expr_unary(ir_unary_operation_t operation, ir_node_t *operand, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_UNARY, diag_loc);
    node->expr_unary.operation = operation;
    node->expr_unary.operand = operand;
    return node;
}

ir_node_t *ir_node_make_expr_var(const char *name, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_VAR, diag_loc);
    node->expr_var.name = name;
    return node;
}

ir_node_t *ir_node_make_expr_call(const char *name, size_t argument_count, ir_node_t **arguments, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_CALL, diag_loc);
    node->expr_call.name = name;
    node->expr_call.argument_count = argument_count;
    node->expr_call.arguments = arguments;
    return node;
}

ir_node_t *ir_node_make_expr_cast(ir_node_t *value, ir_type_t *type, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_EXPR_CAST, diag_loc);
    node->expr_cast.value = value;
    node->expr_cast.type = type;
    return node;
}

ir_node_t *ir_node_make_stmt_block(size_t statement_count, ir_node_t **statements, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_STMT_BLOCK, diag_loc);
    node->stmt_block.statement_count = statement_count;
    node->stmt_block.statements = statements;
    return node;
}

ir_node_t *ir_node_make_stmt_return(ir_node_t *value, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_STMT_RETURN, diag_loc);
    node->stmt_return.value = value;
    return node;
}

ir_node_t *ir_node_make_stmt_if(ir_node_t *condition, ir_node_t *body, ir_node_t *else_body, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_STMT_IF, diag_loc);
    node->stmt_if.condition = condition;
    node->stmt_if.body = body;
    node->stmt_if.else_body = else_body;
    return node;
}

ir_node_t *ir_node_make_stmt_while(ir_node_t *condition, ir_node_t *body, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_STMT_WHILE, diag_loc);
    node->stmt_while.condition = condition;
    node->stmt_while.body = body;
    return node;
}

ir_node_t *ir_node_make_stmt_decl(ir_type_t *type, const char *name, ir_node_t *initial, diag_loc_t diag_loc) {
    ir_node_t *node = make_node(IR_NODE_TYPE_STMT_DECL, diag_loc);
    node->stmt_decl.type = type;
    node->stmt_decl.name = name;
    node->stmt_decl.initial = initial;
    return node;
}