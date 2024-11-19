import os
import subprocess

def run_command(args, process_name, cwd=None):
    try:
        command = subprocess.Popen(args, text=True, cwd=cwd)
        exit_code = command.wait()
        print(f"{process_name} finished with exit code {exit_code}")
        if exit_code != 0:
            raise RuntimeError(f"{process_name} failed with exit code {exit_code}")
    except Exception as e:
        print(f"Error during {process_name}: {e}")
        exit(1)
        
def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(script_dir, 'build')

    os.makedirs(build_dir, exist_ok=True)
    
    run_command(['cmake', '-DCMAKE_BUILD_TYPE=Release', '..'], 'Generate build files', build_dir)
    run_command(['cmake', '--build', '.', '--config', 'Release'], 'Build the project', build_dir)

if __name__ == '__main__':
    main()