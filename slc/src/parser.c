#include "../include/parser.h"
#include "../include/arena_allocator.h"
#include "../include/ast_node.h"
#include "../include/list.h"
#include "../include/token.h"
#include "../include/slc.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct parser_struct {
    list *token_list;
    list_node *current_token_list_node;
} parser;

static parser *parser_create(list *token_list) {
    parser *parser = arena_allocator_allocate(sizeof(struct parser_struct));
    parser->token_list = token_list;
    parser->current_token_list_node = list_get_begin(token_list);
    return parser;
}

static bool parser_tokens_in_bound(parser *parser) {
    return parser->current_token_list_node != list_get_end(parser->token_list);
}

static token *parser_current_token(parser *parser) {
    return parser_tokens_in_bound(parser) ? list_node_get_data(parser->current_token_list_node) : NULL;
}

static token *parser_next_token(parser *parser) {
    return list_node_get_data(list_node_get_next(parser->current_token_list_node));
}

static void parser_advance(parser *parser) {
    parser->current_token_list_node = list_node_get_next(parser->current_token_list_node);
}

static void parser_print_expected_token(token_type type) {
    printf("was expecting: ");
    token_type_print(type);
    printf("\n");
}

static token *parser_seek_token(parser *parser, token_type type) {
    token *current_token = parser_current_token(parser);
    if (!current_token) {
        return NULL;
    }
    if (token_get_type(current_token) != type) {
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: unexpected token: ");
        token_print(current_token);
        printf("; ");
        parser_print_expected_token(type);
        exit(1);
    } else {
        parser_advance(parser);
        return current_token;
    }
}

static ast_node_var *parser_parse_variable(parser *parser) {
    token *token_variable_name = parser_seek_token(parser, TOKEN_IDENT);
    return ast_node_var_create(token_variable_name);
}

static ast_node_num *parser_parse_num(parser *parser) {
    token *token_num = parser_seek_token(parser, TOKEN_NUM);
    return ast_node_num_create(token_get_name(token_num));
}

static ast_node_expr *parser_parse_expr(parser *parser);
static ast_node_un_expr *parser_parse_un_expr(parser *parser);

static ast_node_bin_expr *parser_parse_bin_expr(ast_node_expr *node_expr_left, parser *parser) {
    ast_node_bin_expr *node_bin_expr = NULL;
    token *current_token = parser_current_token(parser);
    parser_advance(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_PLUS: node_bin_expr = ast_node_bin_expr_create_add(node_expr_left, NULL); break;
    case TOKEN_MINUS: node_bin_expr = ast_node_bin_expr_create_sub(node_expr_left, NULL); break;
    default:
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: Expected an operand. Instead got: ");
        token_print(current_token);
        printf(" \n");
        exit(1);
        break;
    }

    current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_NUM:
    case TOKEN_IDENT:
    case TOKEN_LPAREN:
        ast_node_bin_expr_add_right(node_bin_expr, parser_parse_un_expr(parser));
        return node_bin_expr;
    default:
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: Expected an expression. Instead got: ");
        token_print(current_token);
        printf(" \n");
        exit(1);
        break;
    }
}

static ast_node_paren_expr *parser_parse_paren_expr(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);
    ast_node_paren_expr *node_paren_expr = ast_node_paren_expr_create(parser_parse_expr(parser));
    parser_seek_token(parser, TOKEN_RPAREN);

    return node_paren_expr;
}

static list *parser_parse_call_args(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);

    list *args_list = list_create();
    if (token_get_type(parser_current_token(parser)) != TOKEN_RPAREN) {
        list_push(args_list, parser_parse_expr(parser));
        while (token_get_type(parser_current_token(parser)) == TOKEN_COMMA) {
            parser_advance(parser);
            list_push(args_list, parser_parse_expr(parser));
        }
    }
    parser_seek_token(parser, TOKEN_RPAREN);

    return args_list;
}

static ast_node_call *parser_parse_call(parser *parser) {
    token *name = parser_seek_token(parser, TOKEN_IDENT);
    list *args_list = parser_parse_call_args(parser);

    return ast_node_call_create(name, args_list);
}

static ast_node_un_expr *parser_parse_un_expr(parser *parser) {
    token *current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_NUM: return ast_node_un_expr_create_num(parser_parse_num(parser));
    case TOKEN_IDENT:
        if (token_get_type(parser_next_token(parser)) == TOKEN_LPAREN) {
            return ast_node_un_expr_create_call(parser_parse_call(parser));
        }
        return ast_node_un_expr_create_var(parser_parse_variable(parser));
    case TOKEN_LPAREN: return ast_node_un_expr_create_paren_expr(parser_parse_paren_expr(parser));

    default:
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: Expected an unary expression. Instead got: ");
        token_print(current_token);
        printf(" \n");
        exit(1);
        break;
    }
}

static ast_node_expr *parser_parse_expr(parser *parser) {
    token *current_token = parser_current_token(parser);
    ast_node_expr *node_expr = NULL;
    switch (token_get_type(current_token)) {
    case TOKEN_NUM:
    case TOKEN_IDENT:
    case TOKEN_LPAREN:
        node_expr = ast_node_expr_create_un_expr(parser_parse_un_expr(parser));
        break;
    default:
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: Expected an expression. Instead got: ");
        token_print(current_token);
        printf(" \n");
        exit(1);
        break;
    }
    do {
        current_token = parser_current_token(parser);
        switch (token_get_type(current_token)) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            node_expr = ast_node_expr_create_bin_expr(parser_parse_bin_expr(node_expr, parser));
            break;

        default: return node_expr;
        }
    } while (true);
}

static ast_node_asst *parser_parse_asst(parser *parser) {
    ast_node_var *node_var = parser_parse_variable(parser);
    parser_seek_token(parser, TOKEN_LARROW);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    parser_seek_token(parser, TOKEN_DOT);

    return ast_node_asst_create(node_var, node_expr);
}

static ast_node_decl *parser_parse_decl(parser *parser) {
    parser_seek_token(parser, TOKEN_VAR);
    return parser_parse_asst(parser);
}

static ast_node_scope *parser_parse_scope(parser *parser);

static ast_node_cond *parser_parse_cond(parser *parser) {
    parser_seek_token(parser, TOKEN_IF);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    ast_node_scope *node_scope = parser_parse_scope(parser);

    return ast_node_cond_create(node_expr, node_scope);
}

static ast_node_loop *parser_parse_loop(parser *parser) {
    parser_seek_token(parser, TOKEN_LOOP);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    ast_node_scope *node_scope = parser_parse_scope(parser);

    return ast_node_loop_create(node_expr, node_scope);
}

static ast_node_ret *parser_parse_ret(parser *parser) {
    parser_seek_token(parser, TOKEN_RET);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    parser_seek_token(parser, TOKEN_DOT);
    return ast_node_ret_create(node_expr);
}

static ast_node_stmt *parser_parse_stmt(parser *parser) {
    token *current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_VAR: return ast_node_stmt_create_decl(parser_parse_decl(parser));
    case TOKEN_IDENT: return ast_node_stmt_create_asst(parser_parse_asst(parser));
    case TOKEN_IF: return ast_node_stmt_create_cond(parser_parse_cond(parser));
    case TOKEN_LOOP: return ast_node_stmt_create_loop(parser_parse_loop(parser));
    case TOKEN_RET: return ast_node_stmt_create_ret(parser_parse_ret(parser));

    case TOKEN_EOF:
    case TOKEN_RBRACE:
        return NULL;
    default:
        slc_print_compiler_execuatable_name();
        token_print_pos(current_token);
        printf("[PARSER ERROR]: Expected a statement. Instead got: ");
        token_print(current_token);
        printf(" \n");
        exit(1);
        break;
    }
}

static ast_node_scope *parser_parse_scope(parser *parser) {
    parser_seek_token(parser, TOKEN_LBRACE);
    ast_node_scope *node_scope = ast_node_scope_create();
    for (ast_node_stmt *node_stmt = parser_parse_stmt(parser);
         node_stmt != NULL;
         node_stmt = parser_parse_stmt(parser)) {
        ast_node_scope_add_stmt(node_scope, node_stmt);
    }
    parser_seek_token(parser, TOKEN_RBRACE);

    return node_scope;
}

static list *parser_parse_func_params(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);

    list *params_list = list_create();
    if (token_get_type(parser_current_token(parser)) == TOKEN_IDENT) {
        ast_node_var *param = parser_parse_variable(parser);
        list_push(params_list, param);
        while (token_get_type(parser_current_token(parser)) == TOKEN_COMMA) {
            parser_advance(parser);
            param = parser_parse_variable(parser);
            list_push(params_list, param);
        }
    }

    parser_seek_token(parser, TOKEN_RPAREN);

    return params_list;
}

static ast_node_func *parser_parser_func(parser *parser) {
    parser_seek_token(parser, TOKEN_FUNC);
    token *name = parser_seek_token(parser, TOKEN_IDENT);
    parser_seek_token(parser, TOKEN_COLON);
    list *params_list = parser_parse_func_params(parser);
    parser_seek_token(parser, TOKEN_DEFN);
    ast_node_scope *node_scope = parser_parse_scope(parser);
    return ast_node_func_create(name, params_list, node_scope);
}

ast_node_prog *parser_parse_prog(list *token_list) {
    parser *parser = parser_create(token_list);

    list *funcs_list = list_create();
    while (token_get_type(parser_current_token(parser)) != TOKEN_EOF) {
        list_push(funcs_list, parser_parser_func(parser));
    }

    return ast_node_prog_create(funcs_list);
}