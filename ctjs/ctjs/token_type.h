#pragma once

#include <array>
#include <stdexcept>
#include <string>

namespace ctjs::ast {
enum class TokenType {
  Ampersand,
  AmpersandEquals,
  Arrow,
  Asterisk,
  AsteriskEquals,
  Async,
  Await,
  BigIntLiteral,
  BoolLiteral,
  BracketClose,
  BracketOpen,
  Break,
  Caret,
  CaretEquals,
  Case,
  Catch,
  Class,
  Colon,
  Comma,
  Const,
  Continue,
  CurlyClose,
  CurlyOpen,
  Debugger,
  Default,
  Delete,
  Do,
  DoubleAmpersand,
  DoubleAmpersandEquals,
  DoubleAsterisk,
  DoubleAsteriskEquals,
  DoublePipe,
  DoublePipeEquals,
  DoubleQuestionMark,
  DoubleQuestionMarkEquals,
  Else,
  Enum,
  Eof,
  Equals,
  EqualsEquals,
  EqualsEqualsEquals,
  EscapedKeyword,
  ExclamationMark,
  ExclamationMarkEquals,
  ExclamationMarkEqualsEquals,
  Export,
  Extends,
  Finally,
  For,
  Function,
  GreaterThan,
  GreaterThanEquals,
  Identifier,
  If,
  Implements,
  Import,
  In,
  Instanceof,
  Interface,
  Invalid,
  LessThan,
  LessThanEquals,
  Let,
  Minus,
  MinusEquals,
  MinusMinus,
  New,
  NullLiteral,
  NumericLiteral,
  Package,
  ParenClose,
  ParenOpen,
  Percent,
  PercentEquals,
  Period,
  Pipe,
  PipeEquals,
  Plus,
  PlusEquals,
  PlusPlus,
  Private,
  PrivateIdentifier,
  Protected,
  Public,
  QuestionMark,
  QuestionMarkPeriod,
  RegexFlags,
  RegexLiteral,
  Return,
  Semicolon,
  ShiftLeft,
  ShiftLeftEquals,
  ShiftRight,
  ShiftRightEquals,
  Slash,
  SlashEquals,
  Static,
  StringLiteral,
  Super,
  Switch,
  TemplateLiteralEnd,
  TemplateLiteralExprEnd,
  TemplateLiteralExprStart,
  TemplateLiteralStart,
  TemplateLiteralString,
  This,
  Throw,
  Tilde,
  TripleDot,
  Try,
  Typeof,
  UnsignedShiftRight,
  UnsignedShiftRightEquals,
  UnterminatedRegexLiteral,
  UnterminatedStringLiteral,
  UnterminatedTemplateLiteral,
  Var,
  Void,
  While,
  With,
  Yield,
};

inline auto to_token(TokenType type) -> std::string {
  switch (type) {
    case TokenType::Ampersand:
      return "&";
    case TokenType::AmpersandEquals:
      return "&=";
    case TokenType::Arrow:
      return "=>";
    case TokenType::Asterisk:
      return "*";
    case TokenType::AsteriskEquals:
      return "*=";
    case TokenType::Async:
      return "async";
    case TokenType::Await:
      return "await";
    case TokenType::BigIntLiteral:
      return "BigIntLiteral";
    case TokenType::BoolLiteral:
      return "BoolLiteral";
    case TokenType::BracketClose:
      return "]";
    case TokenType::BracketOpen:
      return "[";
    case TokenType::Break:
      return "break";
    case TokenType::Caret:
      return "^";
    case TokenType::CaretEquals:
      return "^=";
    case TokenType::Case:
      return "case";
    case TokenType::Catch:
      return "catch";
    case TokenType::Class:
      return "class";
    case TokenType::Colon:
      return ":";
    case TokenType::Comma:
      return ",";
    case TokenType::Const:
      return "const";
    case TokenType::Continue:
      return "continue";
    case TokenType::CurlyClose:
      return "}";
    case TokenType::CurlyOpen:
      return "{";
    case TokenType::Debugger:
      return "debugger";
    case TokenType::Default:
      return "default";
    case TokenType::Delete:
      return "delete";
    case TokenType::Do:
      return "do";
    case TokenType::DoubleAmpersand:
      return "&&";
    case TokenType::DoubleAmpersandEquals:
      return "&&=";
    case TokenType::DoubleAsterisk:
      return "**";
    case TokenType::DoubleAsteriskEquals:
      return "**=";
    case TokenType::DoublePipe:
      return "||";
    case TokenType::DoublePipeEquals:
      return "||=";
    case TokenType::DoubleQuestionMark:
      return "??";
    case TokenType::DoubleQuestionMarkEquals:
      return "\?\?=";
    case TokenType::Else:
      return "else";
    case TokenType::Enum:
      return "enum";
    case TokenType::Eof:
      return "eof";
    case TokenType::Equals:
      return "=";
    case TokenType::EqualsEquals:
      return "==";
    case TokenType::EqualsEqualsEquals:
      return "===";
    case TokenType::EscapedKeyword:
      return "EscapedKeyword";
    case TokenType::ExclamationMark:
      return "!";
    case TokenType::ExclamationMarkEquals:
      return "!=";
    case TokenType::ExclamationMarkEqualsEquals:
      return "!==";
    case TokenType::Export:
      return "export";
    case TokenType::Extends:
      return "extends";
    case TokenType::Finally:
      return "finally";
    case TokenType::For:
      return "for";
    case TokenType::Function:
      return "function";
    case TokenType::GreaterThan:
      return ">";
    case TokenType::GreaterThanEquals:
      return ">=";
    case TokenType::Identifier:
      return "Identifier";
    case TokenType::If:
      return "if";
    case TokenType::Implements:
      return "implements";
    case TokenType::Import:
      return "import";
    case TokenType::In:
      return "in";
    case TokenType::Instanceof:
      return "instanceof";
    case TokenType::Interface:
      return "interface";
    case TokenType::Invalid:
      return "Invalid";
    case TokenType::LessThan:
      return "<";
    case TokenType::LessThanEquals:
      return "<=";
    case TokenType::Let:
      return "let";
    case TokenType::Minus:
      return "-";
    case TokenType::MinusEquals:
      return "-=";
    case TokenType::MinusMinus:
      return "--";
    case TokenType::New:
      return "new";
    case TokenType::NullLiteral:
      return "null";
    case TokenType::NumericLiteral:
      return "NumericLiteral";
    case TokenType::Package:
      return "package";
    case TokenType::ParenClose:
      return ")";
    case TokenType::ParenOpen:
      return "(";
    case TokenType::Percent:
      return "%";
    case TokenType::PercentEquals:
      return "%=";
    case TokenType::Period:
      return ".";
    case TokenType::Pipe:
      return "|";
    case TokenType::PipeEquals:
      return "|=";
    case TokenType::Plus:
      return "+";
    case TokenType::PlusEquals:
      return "+=";
    case TokenType::PlusPlus:
      return "++";
    case TokenType::Private:
      return "private";
    case TokenType::PrivateIdentifier:
      return "PrivateIdentifier";
    case TokenType::Protected:
      return "protected";
    case TokenType::Public:
      return "public";
    case TokenType::QuestionMark:
      return "?";
    case TokenType::QuestionMarkPeriod:
      return "?.";
    case TokenType::RegexFlags:
      return "RegexFlags";
    case TokenType::RegexLiteral:
      return "RegexLiteral";
    case TokenType::Return:
      return "return";
    case TokenType::Semicolon:
      return ";";
    case TokenType::ShiftLeft:
      return "<<";
    case TokenType::ShiftLeftEquals:
      return "<<=";
    case TokenType::ShiftRight:
      return ">>";
    case TokenType::ShiftRightEquals:
      return ">>=";
    case TokenType::Slash:
      return "/";
    case TokenType::SlashEquals:
      return "/=";
    case TokenType::Static:
      return "static";
    case TokenType::StringLiteral:
      return "StringLiteral";
    case TokenType::Super:
      return "super";
    case TokenType::Switch:
      return "switch";
    case TokenType::TemplateLiteralEnd:
      return "TemplateLiteralEnd";
    case TokenType::TemplateLiteralExprEnd:
      return "TemplateLiteralExprEnd";
    case TokenType::TemplateLiteralExprStart:
      return "TemplateLiteralExprStart";
    case TokenType::TemplateLiteralStart:
      return "TemplateLiteralStart";
    case TokenType::TemplateLiteralString:
      return "TemplateLiteralString";
    case TokenType::This:
      return "this";
    case TokenType::Throw:
      return "throw";
    case TokenType::Tilde:
      return "~";
    case TokenType::TripleDot:
      return "...";
    case TokenType::Try:
      return "try";
    case TokenType::Typeof:
      return "typeof";
    case TokenType::UnsignedShiftRight:
      return ">>>";
    case TokenType::UnsignedShiftRightEquals:
      return ">>>=";
    case TokenType::UnterminatedRegexLiteral:
      return "UnterminatedRegexLiteral";
    case TokenType::UnterminatedStringLiteral:
      return "UnterminatedStringLiteral";
    case TokenType::UnterminatedTemplateLiteral:
      return "UnterminatedTemplateLiteral";
    case TokenType::Var:
      return "var";
    case TokenType::Void:
      return "void";
    case TokenType::While:
      return "while";
    case TokenType::With:
      return "with";
    case TokenType::Yield:
      return "yield";
    default:
      throw std::out_of_range("Invalid TokenType");
  }
}

inline auto to_string(TokenType type) -> std::string {
  std::array<std::string, 121> names{"Ampersand",
                                     "AmpersandEquals",
                                     "Arrow",
                                     "Asterisk",
                                     "AsteriskEquals",
                                     "Async",
                                     "Await",
                                     "BigIntLiteral",
                                     "BoolLiteral",
                                     "BracketClose",
                                     "BracketOpen",
                                     "Break",
                                     "Caret",
                                     "CaretEquals",
                                     "Case",
                                     "Catch",
                                     "Class",
                                     "Colon",
                                     "Comma",
                                     "Const",
                                     "Continue",
                                     "CurlyClose",
                                     "CurlyOpen",
                                     "Debugger",
                                     "Default",
                                     "Delete",
                                     "Do",
                                     "DoubleAmpersand",
                                     "DoubleAmpersandEquals",
                                     "DoubleAsterisk",
                                     "DoubleAsteriskEquals",
                                     "DoublePipe",
                                     "DoublePipeEquals",
                                     "DoubleQuestionMark",
                                     "DoubleQuestionMarkEquals",
                                     "Else",
                                     "Enum",
                                     "Eof",
                                     "Equals",
                                     "EqualsEquals",
                                     "EqualsEqualsEquals",
                                     "EscapedKeyword",
                                     "ExclamationMark",
                                     "ExclamationMarkEquals",
                                     "ExclamationMarkEqualsEquals",
                                     "Export",
                                     "Extends",
                                     "Finally",
                                     "For",
                                     "Function",
                                     "GreaterThan",
                                     "GreaterThanEquals",
                                     "Identifier",
                                     "If",
                                     "Implements",
                                     "Import",
                                     "In",
                                     "Instanceof",
                                     "Interface",
                                     "Invalid",
                                     "LessThan",
                                     "LessThanEquals",
                                     "Let",
                                     "Minus",
                                     "MinusEquals",
                                     "MinusMinus",
                                     "New",
                                     "NullLiteral",
                                     "NumericLiteral",
                                     "Package",
                                     "ParenClose",
                                     "ParenOpen",
                                     "Percent",
                                     "PercentEquals",
                                     "Period",
                                     "Pipe",
                                     "PipeEquals",
                                     "Plus",
                                     "PlusEquals",
                                     "PlusPlus",
                                     "Private",
                                     "PrivateIdentifier",
                                     "Protected",
                                     "Public",
                                     "QuestionMark",
                                     "QuestionMarkPeriod",
                                     "RegexFlags",
                                     "RegexLiteral",
                                     "Return",
                                     "Semicolon",
                                     "ShiftLeft",
                                     "ShiftLeftEquals",
                                     "ShiftRight",
                                     "ShiftRightEquals",
                                     "Slash",
                                     "SlashEquals",
                                     "Static",
                                     "StringLiteral",
                                     "Super",
                                     "Switch",
                                     "TemplateLiteralEnd",
                                     "TemplateLiteralExprEnd",
                                     "TemplateLiteralExprStart",
                                     "TemplateLiteralStart",
                                     "TemplateLiteralString",
                                     "This",
                                     "Throw",
                                     "Tilde",
                                     "TripleDot",
                                     "Try",
                                     "Typeof",
                                     "UnsignedShiftRight",
                                     "UnsignedShiftRightEquals",
                                     "UnterminatedRegexLiteral",
                                     "UnterminatedStringLiteral",
                                     "UnterminatedTemplateLiteral",
                                     "Var",
                                     "Void",
                                     "While",
                                     "With",
                                     "Yield"};
  auto index{static_cast<int>(type)};
  if (index < 0 || index >= static_cast<int>(TokenType::Yield)) {
    throw std::out_of_range("TokenType not supported by to_string()");
  }
  return names[static_cast<int>(type)];
}
}  // namespace ctjs::ast
