#!/bin/bash
# Автоматический запуск с glibc 2.38
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Запускаем с glibc 2.38
exec /opt/glibc-2.38/lib/ld-linux-x86-64.so.2 \
  --library-path "/opt/glibc-2.38/lib:/usr/local/lib:/usr/lib/x86_64-linux-gnu" \
  "${SCRIPT_DIR}/build/optor" "$@"
