#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
exit
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Commands run with no pipes" {
	run "./dsh" << EOF
echo "hello"
exit
EOF
	
	stripped_output=$(echo "$output" | tr -d '[:space:]')
	expected_output="hellodsh3>dsh3>cmdloopreturned0"

	echo "Captured stdout:"
	echo "Output: $output"
	echo "Exit Status: $status"
	echo "${stripped_output} -> ${expected_output}"

	[ "$stripped_output" = "$expected_output" ]

	[ "$status" -eq 0 ]
}

@test "Commands run with one pipe" {
    run "./dsh" << EOF
ls | grep ".c"
exit
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh_cli.cdshlib.cdsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Commands run with multiple pipes" {
    run "./dsh" << EOF
ls | grep ".c" | wc -l
exit
EOF

	stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="2dsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Can pipe up to eight commands without error" {
    run "./dsh" << EOF
test | test | test | test | test | test | test | test
exit
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Piping over eight commands returns error" {
    run "./dsh" << EOF
test | test | test | test | test | test | test | test | test
exit
EOF

	stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh3>error:pipinglimitedto8commandsdsh3>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}
