#!/bin/bash

echo "Testing calculator with various expressions..."

# Function to test calculator
test_expression() {
    local expr="$1"
    local expected="$2"
    echo "Testing: $expr"
    result=$(echo "$expr" | ./calculator | grep "Output:" | sed 's/Output: //')
    if [ "$result" = "$expected" ]; then
        echo "✓ PASS: $result"
    else
        echo "✗ FAIL: Expected $expected, got $result"
    fi
    echo
}

# Test basic operations
test_expression "123 + 456" "579"
test_expression "1000 - 999" "1"
test_expression "123 * 456" "56088"

# Test with parentheses
test_expression "(2 + 3) * 4" "20"
test_expression "2 * (3 + 4)" "14"
test_expression "(10 - 5) * (3 + 2)" "25"

# Test nested parentheses
test_expression "((2 + 3) * 2) + 1" "11"
test_expression "2 * ((3 + 4) * 2)" "28"

# Test negative numbers
test_expression "-5 + 10" "5"
test_expression "10 + (-5)" "5"
test_expression "(-5) * 3" "-15"

# Test complex expression
test_expression "(123 + 456) * (789 - 123)" "385614"

echo "Testing complete!"