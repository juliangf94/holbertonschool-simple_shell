#!/bin/bash
# test_shell.sh - Tests automatiques pour simple_shell Holberton

SHELL="./hsh"  # Remplace par le nom de ton exécutable si besoin
TMPFILE=$(mktemp)

echo "=== Simple Shell Automated Tests ==="
echo

# --- Test 1 : built-in env ---
echo "1. Built-in env"
echo "env" | $SHELL > $TMPFILE
if grep -q "PATH=" $TMPFILE; then
	echo "✅ env OK"
else
	echo "❌ env FAILED"
fi

# --- Test 2 : built-in exit ---
echo "2. Built-in exit"
(echo "exit") | $SHELL >/dev/null
if [ $? -eq 0 ]; then
	echo "✅ exit OK"
else
	echo "❌ exit FAILED"
fi

# --- Test 3 : commande valide PATH ---
echo "3. Commande valide (ls)"
echo "ls" | $SHELL > $TMPFILE
if [ $? -eq 0 ] && [ -n "$(cat $TMPFILE)" ]; then
	echo "✅ ls OK"
else
	echo "❌ ls FAILED"
fi

# --- Test 4 : commande inexistante ---
echo "4. Commande inexistante"
echo "foobar" | $SHELL > $TMPFILE 2>&1
if grep -q "not found" $TMPFILE; then
	echo "✅ foobar not found OK"
else
	echo "❌ foobar not found FAILED"
fi

# --- Test 5 : chemin relatif/absolu ---
echo "5. Chemin relatif/absolu"
touch myprog
chmod -x myprog
echo "./myprog" | $SHELL > $TMPFILE 2>&1
if grep -q "Permission denied" $TMPFILE; then
	echo "✅ ./myprog permission denied OK"
else
	echo "❌ ./myprog permission denied FAILED"
fi
rm myprog

# --- Test 6 : commande absolue ---
echo "6. Commande absolue /bin/ls"
echo "/bin/ls" | $SHELL > $TMPFILE
if [ $? -eq 0 ] && [ -n "$(cat $TMPFILE)" ]; then
	echo "✅ /bin/ls OK"
else
	echo "❌ /bin/ls FAILED"
fi

# --- Test 7 : commande avec arguments ---
echo "7. Commande avec arguments"
echo "echo hello world" | $SHELL > $TMPFILE
if grep -q "hello world" $TMPFILE; then
	echo "✅ echo arguments OK"
else
	echo "❌ echo arguments FAILED"
fi

# --- Test 8 : Ctrl+D simulation ---
echo "8. Ctrl+D simulation"
(echo -n "") | $SHELL >/dev/null
if [ $? -eq 0 ]; then
	echo "✅ Ctrl+D OK"
else
	echo "❌ Ctrl+D FAILED"
fi

# Nettoyage
rm -f $TMPFILE
echo
echo "=== Tests terminés ==="
