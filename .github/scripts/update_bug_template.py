#!/usr/bin/env python3
# .github/scripts/update_bug_template.py
#
# Updates version placeholder values in the GitHub bug report template
# (.github/ISSUE_TEMPLATE/bug.yml) without reformatting the file.
#
# Called by the versioning workflow on every release to keep the placeholder
# hints in sync with the current release versions.
#
# Usage:
#   python3 update_bug_template.py <template> <tft> <firmware> <blueprint>
#
# Arguments:
#   template   Path to the bug report template YAML file.
#   tft        Minimum required TFT version (e.g. "15").
#   firmware   Current ESPHome firmware version (e.g. "2026.4.2").
#   blueprint  Minimum required Blueprint version (e.g. "2026.4.2").
#
# Each placeholder is located by the label that precedes it, making the
# update index-independent and safe against future template reordering.

import re
import sys


def update_placeholder(content: str, label: str, value: str) -> str:
    """Replace the placeholder value following a given label field.

    Matches the label and the next placeholder: line using a non-greedy
    DOTALL pattern, replacing only the value after 'e.g., '.

    Args:
        content: Full file content as a string.
        label:   The label text to anchor the search (e.g. 'TFT Version').
        value:   The new placeholder value to set.

    Returns:
        Updated file content with the placeholder replaced.
        Returns content unchanged if the label is not found.
    """
    pattern = r'(label: ' + re.escape(label) + r'\b.*?placeholder: )e\.g\.,.*'
    replacement = r'\g<1>e.g., ' + value
    return re.sub(pattern, replacement, content, flags=re.DOTALL, count=1)


def main() -> None:
    if len(sys.argv) != 5:
        print(
            f'Usage: {sys.argv[0]} <template> <tft> <firmware> <blueprint>',
            file=sys.stderr,
        )
        sys.exit(1)

    template_path = sys.argv[1]
    tft_version = sys.argv[2]
    firmware_version = sys.argv[3]
    blueprint_version = sys.argv[4]

    with open(template_path, encoding='utf-8') as f:
        content = f.read()

    content = update_placeholder(content, 'TFT Version', tft_version)
    content = update_placeholder(content, 'Firmware Version', firmware_version)
    content = update_placeholder(content, 'Blueprint Version', blueprint_version)

    with open(template_path, 'w', encoding='utf-8') as f:
        f.write(content)

    print(f'Updated placeholders in {template_path}:')
    print(f'  TFT Version:       e.g., {tft_version}')
    print(f'  Firmware Version:  e.g., {firmware_version}')
    print(f'  Blueprint Version: e.g., {blueprint_version}')


if __name__ == '__main__':
    main()
