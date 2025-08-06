// meraParser.js
class Token {
  constructor(type, value, line, col) {
    this.type = type
    this.value = value
    this.line = line
    this.col = col
  }
}

class Lexer {
  constructor(text) {
    this.text = text
    this.pos = 0
    this.line = 1
    this.col = 1
  }

  isAlpha(ch) {
    return /[a-zA-Z_]/.test(ch)
  }
  isDigit(ch) {
    return /[0-9]/.test(ch)
  }
  isAlnum(ch) {
    return this.isAlpha(ch) || this.isDigit(ch)
  }

  nextChar() {
    if (this.pos >= this.text.length) return null
    const ch = this.text[this.pos++]
    if (ch === '\n') {
      this.line++
      this.col = 1
    } else {
      this.col++
    }
    return ch
  }

  peekChar() {
    return this.pos < this.text.length ? this.text[this.pos] : null
  }

  tokenize() {
    let tokens = []
    while (true) {
      let ch = this.peekChar()
      if (ch === null) break

      if (/\s/.test(ch)) {
        this.nextChar()
        continue
      }

      if (ch === '/' && this.text[this.pos + 1] === '/') {
        // Single line comment
        while (ch !== '\n' && ch !== null) {
          ch = this.nextChar()
        }
        continue
      }

      if (this.isAlpha(ch)) {
        let startCol = this.col
        let id = ''
        while (this.isAlnum(this.peekChar())) {
          id += this.nextChar()
        }
        // Keywords vs Identifiers
        const keywords = new Set(['capsule','func','var','const','import','return','if','else','while','for','break','continue','macro','endmacro','when','true','false'])
        if (keywords.has(id)) {
          tokens.push(new Token('keyword', id, this.line, startCol))
        } else {
          tokens.push(new Token('identifier', id, this.line, startCol))
        }
        continue
      }

      if (this.isDigit(ch)) {
        let startCol = this.col
        let num = ''
        while (this.isDigit(this.peekChar())) {
          num += this.nextChar()
        }
        tokens.push(new Token('number', num, this.line, startCol))
        continue
      }

      // Strings
      if (ch === '"') {
        this.nextChar()
        let str = ''
        while (this.peekChar() !== '"' && this.peekChar() !== null) {
          str += this.nextChar()
        }
        this.nextChar() // Consume closing quote
        tokens.push(new Token('string', str, this.line, this.col))
        continue
      }

      // Operators and punctuation
      const ops = ['+','-','*','/','%','=','==','!=','<','>','<=','>=','&&','||','!','(',')','{','}',';',',',':']
      for (let op of ops) {
        if (this.text.startsWith(op, this.pos)) {
          for (let i = 0; i < op.length; i++) this.nextChar()
          tokens.push(new Token('operator', op, this.line, this.col))
          continue
        }
      }

      // Unknown char
      this.nextChar()
    }
    return tokens
  }
}

// Simple recursive descent parser placeholder, you can expand to full AST
class Parser {
  constructor(tokens) {
    this.tokens = tokens
    this.pos = 0
  }

  peek() {
    return this.pos < this.tokens.length ? this.tokens[this.pos] : null
  }

  consume() {
    return this.pos < this.tokens.length ? this.tokens[this.pos++] : null
  }

  parse() {
    // Implement your grammar parsing here; return AST or diagnostics
    return { ast: null, diagnostics: [] }
  }
}

module.exports = { Lexer, Parser }
