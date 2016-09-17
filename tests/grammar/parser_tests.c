#include "parser_tests.h"

#include <string.h>

#include <grammar/lexer.h>
#include <grammar/parser.h>
#include <util/file_utils.h>
#include <util/mem_utils.h>
#include <util/log.h>

#include "helper.h"

static ParserContext* setup(char* fname)
{
	ParserContext* parser;

	if (file_exists(fname))
		parser = init_parser(fname);
	else
		log_kill("test file does not exist");

	return parser;
}

void variable_declaration_test()
{
	ParserContext* parser = setup("res/variable_declaration.x");
	List* ast = parse(parser);

	ASTNode** EXPECTED = malloc(sizeof(ASTNode) * 1);
	
	EXPECTED[0] = 
		mock_ast_node(AST_TYPE_VARIABLE_DECLARATION,
			mock_ast_variable_declaration(
				mock_token(TOK_TYPE_U16, NULL, mock_token_pos(1, 1), 3),
				mock_token(TOK_IDENT, mock_token_value(TOK_IDENT, "x"), mock_token_pos(1, 4), 1)
			)
		);
	EXPECTED[1] =
		mock_ast_node(AST_TYPE_VARIABLE_DECLARATION,
			mock_ast_variable_declaration(
				mock_token(TOK_TYPE_U32, NULL, mock_token_pos(3, 1), 3),
				mock_token(TOK_IDENT, mock_token_value(TOK_IDENT, "y"), mock_token_pos(3, 4), 1)
			)
		);
	
	ASTNode* node = NULL;
	
	List* list = init_list_objects(&destroy_ast_node);
	
	for (size_t i = 0; i < ast->size; i++) {
		node = list_get(ast, i);
		list_append(list, node);
		//ast_dump(list);
		check_ast_node(node, EXPECTED[i]);
	}

	for (int i = 0; i < 2; i++)
		destroy_ast_node(EXPECTED[i]);
	
	log_info("PASS\n");
	destroy_parser(parser);
	destroy_list(list);
}

void parser_tests()
{
	variable_declaration_test();
}
