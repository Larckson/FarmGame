#!/usr/bin/env python3
"""
C Linter for FarmGame
=====================
Rules enforced for all .c files:

  1.  NO_SPACE_IN_EXPR      - No spaces inside expressions (around = += -= *= /=
                               ++ --, and no space between a name and its '(').
  2.  SNAKE_CASE_VAR        - Variable declarations must be snake_case.
  3.  BRACE_OPEN_SPACE      - '{' must be preceded by a space or '=' and be followed by either a new line or a space
  4.  BRACE_CLOSE_NEWLINE   - '}' must be followed by a newline, ';', ',', or ' '
  5.  NO_TYPEDEF            - 'typedef' is forbidden.
  6.  DEFINE_UPPERCASE      - #define names must be ALLCAPS with no underscores.
  7.  INCLUDE_EXT           - #include must reference a .c or .asm file.
  8.  SNAKE_CASE_FUNC       - Function definitions must have snake_case names.
  9.  NO_HEADER_FILES       - .h files are not allowed
 10. NO_COMMA_SPACING       - Commas must never have spaces before or after them.

Exit code: 0 = clean, 1 = violations found.
"""

import re
import sys
from pathlib import Path
from dataclasses import dataclass
from typing import List

@dataclass
class Violation:
    filepath: str
    line_no: int
    col: int
    rule: str
    message: str
    source_line: str


def strip_strings_and_comments(source: str) -> str:
    result = []
    i = 0
    n = len(source)
    while i < n:
        if source[i:i+2] == '/*':
            result.append('/')
            result.append('*')
            i += 2
            while i < n:
                if source[i:i+2] == '*/':
                    result.append('*')
                    result.append('/')
                    i += 2
                    break
                result.append('\n' if source[i] == '\n' else ' ')
                i += 1
            continue
        if source[i:i+2] == '//':
            result.append('/')
            result.append('/')
            i += 2
            while i < n and source[i] != '\n':
                result.append(' ')
                i += 1
            continue
        if source[i] == '"':
            result.append('"')
            i += 1
            while i < n:
                c = source[i]
                if c == '\\':
                    result.append(' ')
                    result.append(' ')
                    i += 2
                    continue
                if c == '"':
                    result.append('"')
                    i += 1
                    break
                result.append('\n' if c == '\n' else ' ')
                i += 1
            continue
        if source[i] == "'":
            result.append("'")
            i += 1
            while i < n:
                c = source[i]
                if c == '\\':
                    result.append(' ')
                    result.append(' ')
                    i += 2
                    continue
                if c == "'":
                    result.append("'")
                    i += 1
                    break
                result.append('\n' if c == '\n' else ' ')
                i += 1
            continue
        result.append(source[i])
        i += 1
    return ''.join(result)

def is_snake_case(name: str) -> bool:
    return bool(re.match(r'^[a-z_][a-z0-9_]*$', name))

_ALL_CAPS_RE = re.compile(r'^[A-Z][A-Z0-9_]*$')

_C_CONTROL_KEYWORDS = {
    'if', 'for', 'while', 'switch', 'return',
    'sizeof', 'typeof', '__attribute__', 'else',
    'do', 'case', 'default',
}

_C_TYPE_KEYWORDS = {
    'int', 'char', 'void', 'float', 'double', 'long',
    'short', 'unsigned', 'signed', 'struct', 'enum', 'union',
}

_SPACE_IN_EXPR_PATTERNS = [
    (r'(?<![=!<>])(\s)(=)(?!=)', "Space before '=' assignment operator"),
    (r'(?<![=!<>])(=)(?!=)(\s)', "Space after '=' assignment operator"),
    (r'(?<![+!<>])(\s)(\+)(?!\+)', "Space before '+' assignment operator"),
    (r'(?<![+!<>])(\+)(?!\+)(\s)', "Space after '+' assignment operator"),
    (r'(\s)(\+=|-=|\*=|/=|%=)', "Space before compound assignment operator"),
    (r'(\+=|-=|\*=|/=|%=)(\s)', "Space after compound assignment operator"),
    (r'(\+\+|--)(\s+)(?=[a-zA-Z_])', "Space between '++'/'--' and its operand"),
    (r'(?<=[a-zA-Z_0-9])(\s+)(\+\+|--)', "Space between operand and '++'/'--'"),
    (r'(?<=[a-zA-Z_0-9])( +)(\()', "Space between function/macro name and '('"),
]

_COMPILED_EXPR = [(re.compile(p), m) for p, m in _SPACE_IN_EXPR_PATTERNS]

def check_spaces_in_expressions(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if stripped.startswith('#') or not stripped:
            continue
        for pattern, msg in _COMPILED_EXPR:
            for m in pattern.finditer(clean):
                col = m.start() + 1
                if msg.startswith("Space between function"):
                    before = clean[:m.start()]
                    word_m = re.search(r'\b([a-zA-Z_]\w*)$', before)
                    if word_m and word_m.group(1) in _C_CONTROL_KEYWORDS:
                        continue
                violations.append(Violation(
                    filepath=filepath, line_no=line_no, col=col,
                    rule="NO_SPACE_IN_EXPR", message=msg,
                    source_line=raw.rstrip(),
                ))
    return violations

def check_comma_spacing(filepath, lines, clean_lines):
    violations = []
    has_override = False
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if ("comma spacing override" in raw):
            has_override = not has_override
        if stripped.startswith('#') or not stripped:
            continue
        if has_override:
            continue

        for m in re.finditer(r' ,|, ', clean):
            col = m.start() + 1
            violations.append(Violation(
                filepath=filepath,
                line_no=line_no,
                col=col,
                rule="NO_COMMA_SPACING",
                message="Commas must not have spaces before or after them",
                source_line=raw.rstrip(),
            ))
    return violations

_DECL_RE = re.compile(
    r'^\s*'
    r'(?:(?:unsigned|signed|static|const|volatile|extern)\s+)*'
    r'(?:(?:int|char|float|double|long|short|void|size_type|'
    r'struct\s+\w+|enum\s+\w+)\s+)'
    r'[\*]*'
    r'([a-zA-Z_][a-zA-Z0-9_]*)'
    r'\s*(?:\[.*?\]\s*)*'
    r'\s*(?:[=;,\)]|$)'
)

_DECL_PTR_RE = re.compile(
    r'^\s*'
    r'(?:(?:unsigned|signed|static|const|volatile|extern)\s+)*'
    r'(?:(?:int|char|float|double|long|short|void|size_type|'
    r'struct\s+\w+|enum\s+\w+)\s+)'
    r'\s*\*\s*'
    r'([a-zA-Z_][a-zA-Z0-9_]*)'
    r'\s*(?:[=;,\)]|$)'
)

_FUNC_DEF_RE = re.compile(
    r'^\s*(?:(?:unsigned|signed|static|const|volatile|extern|void|int|'
    r'char|float|double|long|short)\s+)+'
    r'[a-zA-Z_]\w*\s*\('
)

def check_variable_names(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if stripped.startswith('#') or not stripped:
            continue
        for decl_re in (_DECL_RE, _DECL_PTR_RE):
            m = decl_re.match(clean)
            if not m:
                continue
            name = m.group(1)
            if _ALL_CAPS_RE.match(name):
                continue
            if _FUNC_DEF_RE.match(clean):
                continue
            if not is_snake_case(name):
                col = clean.index(name) + 1
                violations.append(Violation(
                    filepath=filepath, line_no=line_no, col=col,
                    rule="SNAKE_CASE_VAR",
                    message=f"Variable '{name}' is not snake_case",
                    source_line=raw.rstrip(),
                ))
    return violations

def check_brace_open(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if stripped.startswith('#') or not stripped:
            continue

        for m in re.finditer(r'\{', clean):
            col = m.start()

            if col > 0 and clean[col - 1] not in (' ', '='):
                violations.append(Violation(
                    filepath=filepath, line_no=line_no, col=col + 1,
                    rule="BRACE_OPEN_SPACE",
                    message="'{' must be preceded by a space or '='",
                    source_line=raw.rstrip(),
                ))

            if col + 1 < len(clean) and clean[col + 1] not in (' ',):
                violations.append(Violation(
                    filepath=filepath, line_no=line_no, col=col + 1,
                    rule="BRACE_OPEN_SPACE",
                    message="'{' must be followed by a space or newline",
                    source_line=raw.rstrip(),
                ))

    return violations

def check_brace_close(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if stripped.startswith('#') or not stripped:
            continue

        for m in re.finditer(r'\}', clean):
            col = m.start()

            if col + 1 < len(clean):
                next_char = clean[col + 1]
                if next_char not in (' ', ';', ','):
                    violations.append(Violation(
                        filepath=filepath, line_no=line_no, col=col + 1,
                        rule="BRACE_CLOSE_NEWLINE",
                        message="'}' must be followed by a newline, space, ';', or ','",
                        source_line=raw.rstrip(),
                    ))

    return violations

_TYPEDEF_RE = re.compile(r'\btypedef\b')

def check_no_typedef(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        m = _TYPEDEF_RE.search(clean)
        if m:
            violations.append(Violation(
                filepath=filepath, line_no=line_no, col=m.start() + 1,
                rule="NO_TYPEDEF",
                message="'typedef' is not allowed",
                source_line=raw.rstrip(),
            ))
    return violations

_DEFINE_RE = re.compile(r'^\s*#\s*define\s+([A-Za-z_]\w*)')
_DEFINE_OK_RE = re.compile(r'^[A-Z][A-Z0-9]*$')

def check_define_uppercase(filepath, lines, _clean_lines):
    violations = []
    for line_idx, raw in enumerate(lines):
        line_no = line_idx + 1
        m = _DEFINE_RE.match(raw)
        if not m:
            continue
        name = m.group(1)
        if not _DEFINE_OK_RE.match(name):
            col = raw.index(name) + 1
            violations.append(Violation(
                filepath=filepath, line_no=line_no, col=col,
                rule="DEFINE_UPPERCASE",
                message=f"#define name '{name}' must be ALL UPPERCASE with no underscores",
                source_line=raw.rstrip(),
            ))
    return violations

_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]')

def check_include_ext(filepath, lines, _clean_lines):
    violations = []
    for line_idx, raw in enumerate(lines):
        line_no = line_idx + 1
        m = _INCLUDE_RE.match(raw)
        if not m:
            continue
        included = m.group(1)
        if not (included.endswith('.c') or included.endswith('.asm')):
            col = raw.index(included) + 1
            violations.append(Violation(
                filepath=filepath, line_no=line_no, col=col,
                rule="INCLUDE_EXT",
                message=f"#include '{included}' is not allowed; only .c and .asm files may be included",
                source_line=raw.rstrip(),
            ))
    return violations

_FUNC_NAME_RE = re.compile(
    r'^\s*'
    r'(?:(?:static|extern|inline|const|volatile|unsigned|signed)\s+)*'
    r'(?:void|int|char|float|double|long|short|unsigned|struct\s+\w+|enum\s+\w+)'
    r'\s*\*?\s*'
    r'([a-zA-Z_]\w*)'
    r'\s*\('
)

def check_function_names(filepath, lines, clean_lines):
    violations = []
    for line_idx, (raw, clean) in enumerate(zip(lines, clean_lines)):
        line_no = line_idx + 1
        stripped = clean.lstrip()
        if stripped.startswith('#') or not stripped:
            continue
        if 'extern' in clean or '__stdcall' in clean:
            continue
        m = _FUNC_NAME_RE.match(clean)
        if not m:
            continue
        name = m.group(1)
        if name in (_C_CONTROL_KEYWORDS | _C_TYPE_KEYWORDS | {'main'}):
            continue
        if _ALL_CAPS_RE.match(name):
            continue
        if not is_snake_case(name):
            col = clean.index(name) + 1
            violations.append(Violation(
                filepath=filepath, line_no=line_no, col=col,
                rule="SNAKE_CASE_FUNC",
                message=f"Function '{name}' is not snake_case",
                source_line=raw.rstrip(),
            ))
    return violations

def check_no_header_files(filepath: str) -> List[Violation]:
    if filepath.endswith('.h'):
        return [Violation(
            filepath=filepath,
            line_no=1,
            col=1,
            rule="NO_HEADER_FILES",
            message=".h files are not allowed",
            source_line="",
        )]
    return []

def lint_file(filepath: str) -> List[Violation]:
    violations: List[Violation] = []
    violations.extend(check_no_header_files(filepath))
    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as fh:
            source = fh.read()
    except OSError as exc:
        print(f"ERROR: cannot open {filepath}: {exc}", file=sys.stderr)
        return violations
    lines = source.splitlines()
    clean_source = strip_strings_and_comments(source)
    clean_lines = clean_source.splitlines()
    while len(clean_lines) < len(lines):
        clean_lines.append('')
    violations.extend(check_spaces_in_expressions(filepath, lines, clean_lines))
    violations.extend(check_variable_names(filepath, lines, clean_lines))
    violations.extend(check_brace_open(filepath, lines, clean_lines))
    violations.extend(check_brace_close(filepath, lines, clean_lines))
    violations.extend(check_no_typedef(filepath, lines, clean_lines))
    violations.extend(check_define_uppercase(filepath, lines, clean_lines))
    violations.extend(check_include_ext(filepath, lines, clean_lines))
    violations.extend(check_function_names(filepath, lines, clean_lines))
    violations.extend(check_comma_spacing(filepath, lines, clean_lines))
    violations.sort(key=lambda v: (v.line_no, v.col))
    return violations

def collect_c_files(paths: List[str]) -> List[str]:
    result = []
    for p in paths:
        path = Path(p)
        if not path.exists():
            print(f"WARNING: path does not exist: {path}", file=sys.stderr)
            continue
        if path.is_dir():
            result.extend(str(f) for f in sorted(path.rglob('*.c')))
        elif path.suffix == '.c':
            result.append(str(path))
    return result

def main() -> int:
    args = sys.argv[1:]
    if not args:
        import os
        script_path = Path(os.path.realpath(__file__))
        script_dir = script_path.parent
        repo_root = script_dir.parent.parent
        src_path = repo_root / 'src'
        if not src_path.exists():
            print(f"ERROR: Could not find src/ folder at: {src_path}", file=sys.stderr)
            return 1
        args = [str(src_path)]
    files = collect_c_files(args)
    total_violations = 0
    for filepath in files:
        violations = lint_file(filepath)
        for v in violations:
            total_violations += 1
            print(f"{v.filepath}:{v.line_no}:{v.col} [{v.rule}] {v.message}")
    if total_violations:
        print(f"Lint FAILED: {total_violations} violation(s).")
        return 1
    print("Lint PASSED")
    return 0

if __name__ == '__main__':
    sys.exit(main())
