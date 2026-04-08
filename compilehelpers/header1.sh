set -e
TMP=$(mktemp /tmp/run.XXXXXX)
trap 'rm -f "$TMP"' EXIT
dd if="$0" bs=1 skip=LINUX_OFF__ count=LINUX_SZ___ 2>/dev/null > "$TMP"
chmod +x "$TMP"
exec "$TMP" "$@"
