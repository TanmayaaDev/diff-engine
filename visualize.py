import os
import csv
import matplotlib.pyplot as plt  # type: ignore[import-not-found]


def plot_lorenz_trajectories(csv_file="lorenz_output.csv"):
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found. Run the C simulation first!")
        return

    with open(csv_file, newline="") as file:
        rows = list(csv.DictReader(file))

    try:
        x = [float(row["x"]) for row in rows]
        y = [float(row["y"]) for row in rows]
        z = [float(row["z"]) for row in rows]
    except (KeyError, ValueError) as error:
        print(f"Error: invalid CSV data in {csv_file}: {error}")
        return

    # 1. 3D State Space Trajectory Plot
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection="3d")
    ax.plot(x, y, z, lw=0.5, color="crimson")
    ax.set_title("Lorenz Attractor Trajectory (RK4 Integration)")
    ax.set_xlabel("X State")
    ax.set_ylabel("Y State")
    ax.set_zlabel("Z State")
    plt.tight_layout()
    plt.savefig("lorenz_3d_trajectory.png", dpi=300)
    print("Saved 3D plot to lorenz_3d_trajectory.png")

    # 2. 2D Phase Portraits
    fig, axes = plt.subplots(1, 3, figsize=(15, 4.5))

    axes[0].plot(x, y, lw=0.4, color="navy")
    axes[0].set_title("Phase Plane: X vs Y")
    axes[0].set_xlabel("X")
    axes[0].set_ylabel("Y")

    axes[1].plot(x, z, lw=0.4, color="darkgreen")
    axes[1].set_title("Phase Plane: X vs Z")
    axes[1].set_xlabel("X")
    axes[1].set_ylabel("Z")

    axes[2].plot(y, z, lw=0.4, color="purple")
    axes[2].set_title("Phase Plane: Y vs Z")
    axes[2].set_xlabel("Y")
    axes[2].set_ylabel("Z")

    plt.tight_layout()
    plt.savefig("lorenz_phase_portraits.png", dpi=300)
    print("Saved Phase Portraits to lorenz_phase_portraits.png")


if __name__ == "__main__":
    plot_lorenz_trajectories()