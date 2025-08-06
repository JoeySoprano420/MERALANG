const { Lexer, Parser } = require('./meraParser')

// Inside onDidChangeContent or completion, validation handler:
connection.onDidChangeContent(change => {
  const text = change.document.getText()
  const lexer = new Lexer(text)
  const tokens = lexer.tokenize()
  const parser = new Parser(tokens)
  const { ast, diagnostics } = parser.parse()

  connection.sendDiagnostics({ uri: change.document.uri, diagnostics: diagnostics })
})
