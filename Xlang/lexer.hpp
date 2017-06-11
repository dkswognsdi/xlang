#ifndef XLANG_LEXER_HPP
#define XLANG_LEXER_HPP

#include "src_mgr.h"

#include <vector>
#include <string>

class BaseAst
{
public:
	virtual ~BaseAst(void) {}
};

class VariableAst : public BaseAst
{
public:
	VariableAst(std::string &variable_name)
		: variable_name_(variable_name)
	{
	}

	virtual ~VariableAst(void) {}

private:
	std::string variable_name_;
};

class NumericAst : public BaseAst
{
public:
	NumericAst(int numeric_val)
		: numeric_val_(numeric_val)
	{

	}
private:
	int numeric_val_;
};

class BinaryAst : public BaseAst
{
public:
	BinaryAst(std::string &op, BaseAst *lhs, BaseAst rhs)
		: bin_operator_(op), lhs_(lhs), rhs_(rhs)
	{

	}
private:
	std::string bin_operator_;
	BaseAst *lhs_, rhs_;
};

class FunctionDeclAst : public BaseAst
{
public:
	FunctionDeclAst(std::string &func_name, std::vector<std::string> &args)
		: function_name_(func_name), arguments_(args)
	{
	}

private:
	std::string function_name_;
	std::vector<std::string> arguments_;
};

class FunctionDefnAst
{
public:
	FunctionDefnAst(FunctionDeclAst *func_decl_ast, BaseAst *body)
		: func_decl_ast_(func_decl_ast), body_(body)
	{
	}

private:
	FunctionDeclAst *func_decl_ast_;
	BaseAst *body_;
};

class FunctionCallAst : public BaseAst
{
public:
	FunctionCallAst(std::string &function_callee, std::vector<BaseAst *> &function_arguments)
		: function_callee_(function_callee), function_arguments_(function_arguments)
	{
	}

private:
	std::vector<BaseAst *> function_arguments_;
	std::string function_callee_;
};

namespace xlang
{
	class Lexer
	{
	public:
		enum class TokenType
		{
			kEofToken
			, kNumericToken
			, kIdentifierToken
			, kParanToken
			, kFunctionToken
			, kExplainToken
			, kUnknownToken
		};

		Lexer(SourceManager *src_mgr)
			: src_mgr_(src_mgr)
		{
		}

	public:
		bool Lex()
		{
			TokenType tok;

			while (tok != TokenType::kEofToken)
			{
				
			}
		}

		void ProcessToken(TokenType tok)
		{
			//	GetToken 함수에서 이미 첫번째 문자열을 기반으로 분석을 진행했기 때문에 +1	
			
			AddSourceCurrentPos(1);
			
			switch(tok)
			{
			case TokenType::kExplainToken:
				AddSourceCurrentPos(GetExplainContentsSize());
				break;

			default:
				break;
			}
		}

		TokenType GetToken()
		{
			char cur_chr = src_mgr_->GetSourceBuffer()[GetSourceCurrentPos()];
			switch (cur_chr)
			{
			case '#':
				return TokenType::kExplainToken; //시작 문자가 #일 경우 그 줄의 끝까지 주석 처리
			case '@':
				return TokenType::kFunctionToken; //시작 문자가 @일 경우 함수 토큰을 기반으로 처리함
			default:
				return TokenType::kUnknownToken;
			}
			return TokenType::kUnknownToken;
		}

	private:
		unsigned long GetSourceCurrentPos(void) const { return src_current_pos_; }
		void SetSourceCurrentPos(unsigned long pos) { src_current_pos_ = pos; }
		void AddSourceCurrentPos(int val) { src_current_pos_ += val; }

		int GetExplainContentsSize(void)
		{
			int cur_pos = GetSourceCurrentPos();
			unsigned char *src_buf = src_mgr_->GetSourceBuffer();

			int contents_size = 0;
			for (;;)
			{
				if (src_buf[cur_pos + contents_size] == '\n')
					break;

				contents_size++;
			}
			return contents_size;
		}

	private:
		unsigned long src_current_pos_ = 0;
		SourceManager *src_mgr_ = nullptr;
	};
}

#endif