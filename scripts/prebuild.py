import os
import base64
import re
import mimetypes

def remove_comments(html):
    # Remove /* ... */ comments (multi-line)
    html = re.sub(r'/\*.*?\*/', '', html, flags=re.DOTALL)

    # Remove // ... comments (but not inside strings)
    def strip_line_comments(line):
        # Skip lines inside HTML strings
        in_string = False
        quote_char = ''
        for i, c in enumerate(line):
            if c in ('"', "'"):
                if not in_string:
                    in_string = True
                    quote_char = c
                elif c == quote_char:
                    in_string = False
            elif c == '/' and not in_string and i + 1 < len(line) and line[i+1] == '/':
                return line[:i].rstrip()
        return line

    lines = html.splitlines()
    stripped = [strip_line_comments(line) for line in lines]
    return "\n".join(stripped)

def embed_images_as_base64(html, base_path="data"):
    def replacer(match):
        quote = match.group(1)
        path = match.group(2)

        image_path = os.path.join(base_path, path)
        if not os.path.isfile(image_path):
            print(f"[WARN] Image not found: {image_path}")
            return match.group(0)

        mime_type, _ = mimetypes.guess_type(image_path)
        if not mime_type:
            print(f"[WARN] Unknown mime type: {image_path}")
            return match.group(0)

        with open(image_path, "rb") as img_file:
            b64_data = base64.b64encode(img_file.read()).decode('utf-8')

        data_uri = f"url({quote}data:{mime_type};base64,{b64_data}{quote})"
        return data_uri

    pattern = re.compile(r"url\((['\"])(.+?)\1\)")
    return pattern.sub(replacer, html)

def generate_webpage_header():
    html_path = os.path.join("data", "index.html")
    output_path = os.path.join("include", "web_page.h")

    with open(html_path, "r", encoding="utf-8") as f:
        html_content = f.read()

    #html_content = remove_comments(html_content)
    html_content = embed_images_as_base64(html_content, base_path="data")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write('const char MAIN_page[] PROGMEM = R"rawliteral(\n')
        f.write(html_content)
        f.write('\n)rawliteral";\n')

    print("[INFO] web_page.h generated successfully.")

generate_webpage_header()
