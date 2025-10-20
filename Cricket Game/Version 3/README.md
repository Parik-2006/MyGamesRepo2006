# 🏏 Cricket Game (C Language)

A fully interactive **terminal-based Cricket Game** written in **C**.  
Play solo against the **computer**, go head-to-head in a **1 vs 1 PvP**, or team up for an exciting **2 vs 2 team battle** — all within your terminal window!

---

## 🎮 Game Modes

### 🧠 1. Vs Computer  
- Play against the computer with **three difficulty levels**:  
  - 🟢 Easy  
  - 🟡 Medium  
  - 🔴 Hard  
- Perform a **toss** (Heads or Tails) to decide who bats/bowls first.  
- The computer uses random and probability-based guessing depending on difficulty.

---

### ⚔️ 2. 1 vs 1 (PvP)  
- Two players compete directly in the terminal.  
- Each player alternates between **batting** and **bowling**.  
- Real toss determines who starts first.  
- Each match displays a detailed summary and records results in stats files.

---

### 🧍‍♂️🧍‍♀️ 3. 2 vs 2 (Team PvP)  
- Two teams with two players each.  
- Tracks **wickets**, **runs**, and **targets** for both teams.  
- Both teammates get a chance to bat, and the game automatically swaps players on wickets.

---

## ⚙️ Features

✅ Fully interactive and text-based interface  
✅ Realistic **toss system**  
✅ Customizable overs (1–3)  
✅ Selectable difficulty levels for computer matches  
✅ Colored terminal outputs for results (Win/Loss/Tie)  
✅ Auto-clearing screen between plays for cleaner UI  
✅ Persistent **player statistics** across sessions  
✅ Works on both **Windows** and **Linux/macOS terminals**

---

## 🧾 How to Compile and Run

### Step 1: Save the file
Save the source code as:-
cricket_game

### Step 2: Compile using GCC
```bash
gcc cricket_game.c -o cricket_game