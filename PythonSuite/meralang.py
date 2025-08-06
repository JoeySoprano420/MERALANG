import sys
import io
import os

class MeraLang:
    def __init__(self):
        self.scopes = [{}]  # A stack of scopes, starting with the global scope
        self.functions = {}
        self.included_files = set()

    def _get_variable(self, name):
        for scope in reversed(self.scopes):
            if name in scope:
                return scope[name]
        raise RuntimeError(f"Undefined variable: {name}")

    def _set_variable(self, name, value, index=None):
        # Sets a variable in the current (innermost) scope.
        if index is not None:
            # This is an array modification
            for scope in reversed(self.scopes):
                if name in scope:
                    if not isinstance(scope[name], list):
                        raise RuntimeError(f"Variable '{name}' is not an array.")
                    scope[name][index] = value
                    return
            raise RuntimeError(f"Undefined variable: {name}")
        else:
            self.scopes[-1][name] = value

    def strip_comment(self, line):
        pos = line.find('#')
        return line if pos == -1 else line[:pos]

    def trim(self, s):
        return s.strip()

    def eval_factor(self, iss):
        iss.seek(self._skip_whitespace(iss))
        c = iss.read(1)
        if c == '':
            return None # End of expression
        if c == '(':
            val = self.eval_expr(iss)
            iss.seek(self._skip_whitespace(iss))
            closing = iss.read(1)
            if closing != ')':
                raise RuntimeError("Mismatched parentheses")
            return val
        elif c == '[': # Array literal
            return self.parse_array_literal(iss)
        elif c == '-':
            return -self.eval_factor(iss)
        elif c.isdigit():
            num = c
            while True:
                ch = iss.read(1)
                if not ch.isdigit():
                    iss.seek(iss.tell() - 1)
                    break
                num += ch
            return int(num)
        elif c.isalpha():
            var_name = self._read_token(iss, rewind=True)
            
            self._skip_whitespace(iss, update=True)
            next_char_pos = iss.tell()
            next_char = iss.read(1)
            iss.seek(next_char_pos)

            if next_char == '(':
                return self.handle_call(var_name, iss)
            
            val = self._get_variable(var_name)

            # Check for array access
            self._skip_whitespace(iss, update=True)
            next_char_pos = iss.tell()
            if iss.read(1) == '[':
                if not isinstance(val, list):
                    raise RuntimeError(f"Variable '{var_name}' is not an array.")
                index = self.eval_expr(iss)
                self._skip_whitespace(iss, update=True)
                if iss.read(1) != ']':
                    raise RuntimeError("Expected ']' after array index.")
                return val[index]
            else:
                iss.seek(next_char_pos)

            if var_name == "not":
                return not self.eval_factor(iss)
            
            return val
        else:
            iss.seek(iss.tell() - 1) # Put back char
            return None

    def parse_array_literal(self, iss):
        arr = []
        self._skip_whitespace(iss, update=True)
        if iss.read(1) == ']':
            return arr # Empty array
        iss.seek(iss.tell() - 1)

        while True:
            val = self.eval_expr(iss)
            arr.append(val)
            self._skip_whitespace(iss, update=True)
            c = iss.read(1)
            if c == ']':
                break
            if c != ',':
                raise RuntimeError("Expected ',' or ']' in array literal.")
        return arr

    def eval_term(self, iss):
        val = self.eval_factor(iss)
        while val is not None:
            self._skip_whitespace(iss, update=True)
            op_pos = iss.tell()
            op = iss.read(1)
            if op in ('*', '/'):
                rhs = self.eval_factor(iss)
                if rhs is None: raise RuntimeError("Expected expression after operator")
                if op == '*':
                    val *= rhs
                else:
                    if rhs == 0:
                        raise RuntimeError("Division by zero")
                    val //= rhs
            else:
                iss.seek(op_pos)
                break
        return val

    def eval_expr(self, iss):
        val = self.eval_term(iss)
        while val is not None:
            self._skip_whitespace(iss, update=True)
            op_pos = iss.tell()
            op = iss.read(1)
            if op in ('+', '-'):
                rhs = self.eval_term(iss)
                if rhs is None: raise RuntimeError("Expected expression after operator")
                if op == '+':
                    val += rhs
                else:
                    val -= rhs
            else:
                iss.seek(op_pos)
                break
        return val

    def eval_condition(self, cond_str):
        iss = io.StringIO(cond_str)
        return self.eval_logical_or(iss)

    def eval_logical_or(self, iss):
        val = self.eval_logical_and(iss)
        while True:
            self._skip_whitespace(iss, update=True)
            pos = iss.tell()
            op = self._read_token(iss)
            if op == "or":
                rhs = self.eval_logical_and(iss)
                val = val or rhs
            else:
                iss.seek(pos)
                break
        return val

    def eval_logical_and(self, iss):
        val = self.eval_comparison(iss)
        while True:
            self._skip_whitespace(iss, update=True)
            pos = iss.tell()
            op = self._read_token(iss)
            if op == "and":
                rhs = self.eval_comparison(iss)
                val = val and rhs
            else:
                iss.seek(pos)
                break
        return val

    def eval_comparison(self, iss):
        val = self.eval_expr(iss)
        self._skip_whitespace(iss, update=True)
        pos = iss.tell()
        op = self._read_token(iss)
        if op in (">", "<", "==", "!=", ">=", "<="):
            rhs = self.eval_expr(iss)
            if op == ">": return val > rhs
            if op == "<": return val < rhs
            if op == "==": return val == rhs
            if op == "!=": return val != rhs
            if op == ">=": return val >= rhs
            if op == "<=": return val <= rhs
        iss.seek(pos)
        return val

    def print_stmt(self, expr):
        iss = io.StringIO(expr)
        while True:
            self._skip_whitespace(iss, update=True)
            start_pos = iss.tell()
            c = iss.read(1)
            if c == '':
                break
            if c == '"':
                s = ''
                while True:
                    ch = iss.read(1)
                    if ch == '"' or ch == '':
                        break
                    s += ch
                print(s, end='')
            else:
                iss.seek(start_pos)
                val = self.eval_expr(iss)
                if val is not None:
                    # Basic pretty-print for lists
                    if isinstance(val, list):
                        print(f"[{', '.join(map(str, val))}]", end='')
                    else:
                        print(val, end='')
                
                # If eval_expr consumed nothing, we might be stuck.
                if iss.tell() == start_pos:
                    break
        print()

    def run(self, filename):
        try:
            abs_path = os.path.abspath(filename)
            with open(abs_path, 'r') as f:
                lines = f.readlines()
            self.included_files.add(abs_path)
        except Exception:
            print(f"Cannot open file: {filename}")
            return
        
        self.execute_lines(lines)

    def execute_lines(self, lines):
        line_idx = 0
        while line_idx < len(lines):
            line = self.strip_comment(lines[line_idx]).strip()
            
            if not line:
                line_idx += 1
                continue
            
            iss = io.StringIO(line)
            token = self._read_token(iss)

            if token == "let":
                self.handle_let(iss)
            elif token == "print":
                self.handle_print(iss)
            elif token == "input":
                self.handle_input(iss)
            elif token == "include":
                self.handle_include(iss)
            elif token == "if":
                cond_str = self._read_until(iss, 'then').strip()
                rest_of_line = iss.read().strip()
                
                block_lines, end_type, lines_consumed = self.get_block(lines, line_idx + 1, rest_of_line)
                line_idx += lines_consumed

                else_block_lines = []
                if end_type == 'else':
                    else_block_lines, _, lines_consumed = self.get_block(lines, line_idx)
                    line_idx += lines_consumed

                try:
                    if self.eval_condition(cond_str):
                        signal, value = self.execute_lines(block_lines)
                        if signal == 'return': return signal, value
                    elif else_block_lines:
                        signal, value = self.execute_lines(else_block_lines)
                        if signal == 'return': return signal, value
                except Exception as e:
                    print(f"Error: {e}")

            elif token == "while":
                cond_str = self._read_until(iss, 'do').strip()
                rest_of_line = iss.read().strip()

                block_lines, _, lines_consumed = self.get_block(lines, line_idx + 1, rest_of_line)
                line_idx += lines_consumed
                
                try:
                    while self.eval_condition(cond_str):
                        signal, value = self.execute_lines(block_lines)
                        if signal == 'return':
                            return signal, value
                except Exception as e:
                    print(f"Error: {e}")
            
            elif token == "func":
                func_name = self._read_token(iss)
                params, body_lines, lines_consumed = self.handle_func_def(iss, lines, line_idx + 1)
                self.functions[func_name] = {'params': params, 'body': body_lines}
                line_idx += lines_consumed

            elif token == "call":
                func_name = self._read_token(iss)
                self.handle_call(func_name, iss)

            elif token == "return":
                expr = iss.read().strip()
                return_val = self.eval_expr(io.StringIO(expr)) if expr else None
                return ('return', return_val)

            elif token not in ('', 'end', 'else'):
                print(f"Unknown statement: {token}")
            
            line_idx += 1
        return (None, None) # Normal termination

    def get_block(self, lines, start_idx, first_line=""):
        if first_line and first_line != 'begin':
            return [first_line], 'inline', 1
        
        block_lines = []
        level = 1
        idx = start_idx
        
        if first_line != 'begin':
            idx = start_idx - 1

        while idx < len(lines):
            line = self.strip_comment(lines[idx]).strip()
            
            if line.startswith('if') or line.startswith('while') or line.startswith('func'):
                level += 1
            elif line == 'end':
                level -= 1
            elif line == 'else' and level == 1:
                return block_lines, 'else', idx - start_idx + 1

            if level == 0:
                return block_lines, 'end', idx - start_idx + 1
            
            if line not in ('begin', 'end'):
                 block_lines.append(line)
            idx += 1
        
        raise RuntimeError("Unmatched 'begin'. Reached end of file.")

    def handle_let(self, iss):
        var_name = self._read_token(iss)
        index = None

        self._skip_whitespace(iss, update=True)
        pos = iss.tell()
        if iss.read(1) == '[':
            index = self.eval_expr(iss)
            if iss.read(1) != ']':
                raise RuntimeError("Expected ']' in indexed assignment.")
        else:
            iss.seek(pos)

        eq = self._read_token(iss)
        if eq != '=':
            print("Syntax error: expected '='")
            return
        expr = self.trim(iss.read())
        try:
            expr_iss = io.StringIO(expr)
            value = self.eval_expr(expr_iss)
            self._set_variable(var_name, value, index)
        except Exception as e:
            print(f"Error: {e}")

    def handle_print(self, iss):
        expr = self.trim(iss.read())
        try:
            self.print_stmt(expr)
        except Exception as e:
            print(f"Error: {e}")

    def handle_input(self, iss):
        var = self._read_token(iss)
        if not var:
            print("Syntax error: expected variable name for 'input'")
            return
        try:
            user_input = input()
            try:
                self._set_variable(var, int(user_input))
            except ValueError:
                self._set_variable(var, user_input)
        except Exception as e:
            print(f"Error during input: {e}")

    def handle_include(self, iss):
        self._skip_whitespace(iss, update=True)
        if iss.read(1) != '"':
            raise RuntimeError("Expected a string literal for filename after 'include'")
        
        filename = ''
        while True:
            ch = iss.read(1)
            if ch == '"' or ch == '':
                break
            filename += ch
        
        if not filename:
            raise RuntimeError("Empty filename in 'include' statement.")

        try:
            abs_path = os.path.abspath(filename)
            if abs_path in self.included_files:
                return # Prevent circular/repeated includes

            with open(abs_path, 'r') as f:
                included_lines = f.readlines()
            self.included_files.add(abs_path)
        except Exception:
            print(f"Cannot open include file: {filename}")
            return
        
        self.execute_lines(included_lines)

    def handle_func_def(self, iss, lines, start_idx):
        self._skip_whitespace(iss, update=True)
        if iss.read(1) != '(': raise RuntimeError("Expected '(' after function name")
        
        params_str = self._read_until(iss, ')')
        params = [p.strip() for p in params_str.split(',') if p.strip()]
        
        rest_of_line = iss.read().strip()
        body_lines, _, lines_consumed = self.get_block(lines, start_idx, rest_of_line)
        return params, body_lines, lines_consumed

    def handle_call(self, func_name, iss):
        if func_name not in self.functions:
            raise RuntimeError(f"Undefined function: {func_name}")
        
        func = self.functions[func_name]
        
        self._skip_whitespace(iss, update=True)
        if iss.read(1) != '(': raise RuntimeError(f"Expected '(' for call to {func_name}")
        
        args = []
        while True:
            self._skip_whitespace(iss, update=True)
            next_char = iss.read(1)
            if next_char == ')':
                break
            iss.seek(iss.tell() - 1)
            
            arg_val = self.eval_expr(iss)
            args.append(arg_val)
            
            self._skip_whitespace(iss, update=True)
            next_char = iss.read(1)
            if next_char == ')':
                break
            if next_char != ',':
                raise RuntimeError("Expected ',' or ')' in argument list")

        if len(args) != len(func['params']):
            raise RuntimeError(f"Function {func_name} expects {len(func['params'])} arguments, got {len(args)}")

        self.scopes.append({param: arg for param, arg in zip(func['params'], args)})
        signal, return_value = self.execute_lines(func['body'])
        self.scopes.pop()

        if signal == 'return':
            return return_value
        return None

    # --- Utility methods below ---

    def _skip_whitespace(self, iss, update=False):
        pos = iss.tell()
        while True:
            ch = iss.read(1)
            if ch not in (' ', '\t', '\n', '\r'):
                if update:
                    iss.seek(iss.tell() - 1)
                else:
                    iss.seek(pos)
                break
            if ch == '':
                break
            pos = iss.tell()
        return pos

    def _read_token(self, iss, rewind=False):
        self._skip_whitespace(iss, update=True)
        start_pos = iss.tell()
        
        ch = iss.read(1)
        if ch in ('>', '<', '=', '!'):
            next_ch = iss.read(1)
            if next_ch == '=':
                token = ch + next_ch
            else:
                iss.seek(iss.tell() - 1)
                token = ch
        else:
            iss.seek(start_pos)
            token = ''
            while True:
                ch = iss.read(1)
                if ch == '' or not (ch.isalnum() or ch == '_'):
                    iss.seek(iss.tell() - 1)
                    break
                token += ch
        
        if rewind:
            iss.seek(start_pos)

        return token

    def _read_until(self, iss, keyword):
        s = ''
        nesting = 0
        if isinstance(keyword, str):
            keyword = keyword.encode('utf-8')

        while True:
            char = iss.read(1)
            if char == '':
                raise RuntimeError(f"Expected '{keyword.decode('utf-8')}' but reached end of input.")
            
            if char == '(': nesting += 1
            elif char == ')': nesting -= 1

            if char == keyword.decode('utf-8') and nesting < 0:
                return s

            s += char
        return s

    def _read_until_space_or_quote(self, iss):
        s = ''
        while True:
            pos = iss.tell()
            ch = iss.read(1)
            if ch == '' or ch in (' ', '"', '\t', '\n', '\r'):
                iss.seek(pos)
                break
            s += ch
        return s

    def _is_number(self, s):
        try:
            int(s)
            return True
        except:
            return False

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: MeraLangCompiler <source.ml>")
        sys.exit(1)
    compiler = MeraLang()
    compiler.run(sys.argv[1])
    sys.exit(0)

