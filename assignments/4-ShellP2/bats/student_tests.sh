#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
exit
EOF
	# Strip all whitespace
	stripped_output=$(echo "$output" | tr -d '[:space:]')

	#Expected output
	expected_output="batsdshdsh_cli.cdshlib.cdshlib.hmakefiledsh2>dsh2>cmdloopreturned0"

	echo "Captured stdout:"
	echo "Output: $output"
	echo "Exit Status: $status"
	echo "${stripped_output} -> ${expected_output}"

    # Assertions
    [ "$stripped_output" == "$expected_output" ]
}

@test "Check pwd runs without errors" {
	run ./dsh <<EOF
pwd
exit
EOF
	
	# Strip all whitespace
	stripped_output=$(echo "$output" | tr -d '[:space:]')

	# Expected output
	expected_output="/home/arq23/cs283/a4dsh2>dsh2>cmdloopreturned0"

	echo "${stripped_output} -> ${expected_output}"

	# Assertions
	[ "$stripped_output" == "$expected_output" ]
}

@test "Check cd works with proper parameters" {
	run ./dsh <<EOF
pwd
cd bats
pwd
exit
EOF
	
	# Strip all whitespace
	stripped_output=$(echo "$output" | tr -d '[:space:]')

	# Expected output
	expected_output="/home/arq23/cs283/a4/home/arq23/cs283/a4/batsdsh2>dsh2>dsh2>dsh2>cmdloopreturned0"

	echo "${stripped_output} -> ${expected_output}"

	# Assertions
	[ "$stripped_output" == "$expected_output" ]
}

@test "Check cd does nothing with no parameters" {
    run ./dsh <<EOF
pwd
cd
pwd
exit
EOF

	# Strip all whitespace
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output
    expected_output="/home/arq23/cs283/a4/home/arq23/cs283/a4dsh2>dsh2>dsh2>dsh2>cmdloopreturned0"

    echo "${stripped_output} -> ${expected_output}"

    # Assertions
	[ "$stripped_output" == "$expected_output" ]
}

@test "Check cd does nothing with extra parameters" {
    run ./dsh <<EOF
pwd
cd foo bar
pwd
exit
EOF

	# Strip all whitespace
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output
    expected_output="/home/arq23/cs283/a4/home/arq23/cs283/a4dsh2>dsh2>dsh2>dsh2>cmdloopreturned0"

    echo "${stripped_output} -> ${expected_output}"

    # Assertions
	[ "$stripped_output" == "$expected_output" ]
}

@test "External commands work with one parameter" {
	run ./dsh <<EOF
ls
mkdir foo
ls
rmdir foo
exit
EOF

	# Strip all whitespace
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output
	expected_output="batsdshdsh_cli.cdshlib.cdshlib.hmakefilebatsdshdsh_cli.cdshlib.cdshlib.hfoomakefiledsh2>dsh2>dsh2>dsh2>dsh2>cmdloopreturned0"

	echo "${stripped_output} -> ${expected_output}"

	# Assertions
	[ "$stripped_output" == "$expected_output" ]
}

@test "External commands work with multiple parameters" {
    run ./dsh <<EOF
ls
mkdir foo bar
ls
rmdir foo bar
exit
EOF

	# Strip all whitespace
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output
    expected_output="batsdshdsh_cli.cdshlib.cdshlib.hmakefilebarbatsdshdsh_cli.cdshlib.cdshlib.hfoomakefiledsh2>dsh2>dsh2>dsh2>dsh2>cmdloopreturned0"

    echo "${stripped_output} -> ${expected_output}"

    # Assertions
	[ "$stripped_output" == "$expected_output" ]
}
