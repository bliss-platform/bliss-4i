import subprocess
import pathlib
import sys

INTERPRETER_PATH = "../target/debug/interpreter"
TESTS_DIR = pathlib.Path("./tests")


def run_test(test_file):
    print("\n====================================")
    print(f"Running: {test_file}")
    print("====================================")

    result = subprocess.run(
        [INTERPRETER_PATH, str(test_file)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    if result.stdout:
        print("STDOUT:")
        print(result.stdout)

    if result.stderr:
        print("STDERR:")
        print(result.stderr)

    print(f"Exit Code: {result.returncode}")


def main():
    if not TESTS_DIR.exists():
        print("No tests/ directory found.")
        sys.exit(1)

    test_files = [f for f in TESTS_DIR.iterdir() if f.is_file()]

    if not test_files:
        print("No test files found in tests/")
        return

    for test in sorted(test_files):
        run_test(test)


if __name__ == "__main__":
    main()