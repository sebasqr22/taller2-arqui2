import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# Rutas de los ejecutables
BIN_DIR = Path("bin")
SERIAL = BIN_DIR / "case_serial"
SIMD = BIN_DIR / "case_simd"
GENERATOR = BIN_DIR / "generator"
RESULTS_DIR = Path("resultados")
RESULTS_DIR.mkdir(exist_ok=True)

# Parámetros de prueba
TAMANIOS = [10**3, 10**4, 10**5, 10**6]
PORC_LETRAS = 80     # 80% letras y 20% otros
ALINEACION = 32
ITERACIONES = 5      

def generar_texto(size):
    # generar texto
    result = subprocess.run([str(GENERATOR), str(size), str(PORC_LETRAS), str(ALINEACION)],
                            capture_output=True, text=True)
    # extraer solo la cadena generada
    texto = result.stdout.split("\n", 2)[2].strip()
    return texto

def medir_tiempo(ejecutable, texto, modo):
    # ejecucion
    start = time.perf_counter()
    proc = subprocess.run([str(ejecutable), texto, modo],
                          capture_output=True, text=True)
    end = time.perf_counter()
    return end - start

datos = []

for tam in TAMANIOS:
    texto = generar_texto(tam)
    print(f"Probando tam {tam}...")

    for modo in ["upper", "lower"]:
        for tipo, exe in [("serial", SERIAL), ("simd", SIMD)]:
            tiempos = []
            for _ in range(ITERACIONES):
                t = medir_tiempo(exe, texto, modo)
                tiempos.append(t)
            promedio = sum(tiempos) / len(tiempos)
            print(f"{tipo.upper()} ({modo}): {promedio:.6f} s")

            datos.append({
                "tamaño": tam,
                "modo": modo,
                "tipo": tipo,
                "tiempo_s": promedio
            })

# guardar csv
df = pd.DataFrame(datos)
csv_path = RESULTS_DIR / "resultados_benchmark.csv"
df.to_csv(csv_path, index=False)
print(f"\nResultados guardados en {csv_path}")

# generar grafica
plt.figure(figsize=(8, 5))
for modo in ["upper", "lower"]:
    subset = df[df["modo"] == modo]
    plt.plot(subset[subset["tipo"] == "serial"]["tamaño"],
             subset[subset["tipo"] == "serial"]["tiempo_s"],
             "o--", label=f"Serial ({modo})")
    plt.plot(subset[subset["tipo"] == "simd"]["tamaño"],
             subset[subset["tipo"] == "simd"]["tiempo_s"],
             "o-", label=f"SIMD ({modo})")

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Tamaño del texto (log)")
plt.ylabel("Tiempo de ejecución [s] (log)")
plt.title("Comparación Serial vs SIMD")
plt.legend()
plt.grid(True, which="both", ls="--", lw=0.5)
plt.tight_layout()
plt.savefig(RESULTS_DIR / "grafico_benchmark.png")
plt.show()
