import os
import shutil
import subprocess

def run_command(args, process_name, cwd=None):
    try:
        command = subprocess.Popen(args, text=True, cwd=cwd)
        exit_code = command.wait()
        print(f"[ BUILD INFO ] {process_name} finished with exit code {exit_code}")
        if exit_code != 0:
            raise RuntimeError(f"[ BUILD INFO ] {process_name} failed with exit code {exit_code}")
    except Exception as e:
        print(f"[ BUILD ERROR ] Error during {process_name}: {e}")
        exit(1)

def create_build_dir(build_dir):
    if os.path.exists(build_dir) and os.path.isdir(build_dir):
        shutil.rmtree(build_dir)
        print(f"[ BUILD INFO ] Old build directory deleted")
    try:
        os.makedirs(build_dir, exist_ok=True)
        print(f"[ BUILD INFO ] Build directory created at {build_dir}")
    except OSError as e:
        print(f"[ BUILD ERROR ] Failed to create build directory: {e}")
        exit(1)
    

def check_CMakeLists(project_root):
    cmake_file_path = os.path.join(project_root, 'CMakeLists.txt')
    if not os.path.isfile(cmake_file_path):
        print(f"[ BUILD ERROR ] CMakeLists.txt not found in {project_root}")
        exit(1)
    else:
        print(f"[ BUILD INFO ] Found CMakeLists.txt at {cmake_file_path}")
        
def main():

    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    build_dir = os.path.join(project_root, 'build')

    create_build_dir(build_dir)

    check_CMakeLists(project_root)
    
    run_command(['cmake', '-DCMAKE_BUILD_TYPE=Release', '..'], 'Generate build files', build_dir)
    run_command(['cmake', '--build', '.', '--config', 'Release'], 'Build the project', build_dir)

if __name__ == '__main__':
    main()