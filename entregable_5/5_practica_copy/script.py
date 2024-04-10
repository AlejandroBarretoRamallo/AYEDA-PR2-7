import subprocess

def main():
    ruta = "/home/alejandro/ayeda2324/5_practica"
    subprocess.run(["git", "add", "."], cwd=ruta)
    subprocess.run(["git", "commit", "-m", "'a'"], cwd=ruta)
    subprocess.run(["git", "push"], cwd=ruta)

if __name__ == "__main__":
    main()