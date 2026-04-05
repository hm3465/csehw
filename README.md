# Binary Search Tree — README

## Files

| File          | Purpose                                      |
|---------------|----------------------------------------------|
| `bst.py`      | BST implementation (Node + BST classes)      |
| `test_bst.py` | Self-contained test driver (no dependencies) |

## Running the Tests (stdlinux)

```bash
# 1. Clone / copy both files into the same directory, then:
cd bst/
python3 test_bst.py
```

Python 3.6+ is required. No third-party packages are needed.

A successful run ends with:

```
=======================================================
  Results: X/X tests passed  — ALL PASS ✓
=======================================================
```

The script exits with code `0` on success and `1` if any test fails.

---

## Operations & Complexity

| Operation     | Average | Worst case |
|---------------|---------|------------|
| `insert(key)` | O(log n)| O(n)       |
| `delete(key)` | O(log n)| O(n)       |
| `search(key)` | O(log n)| O(n)       |
| `minimum()`   | O(log n)| O(n)       |
| `maximum()`   | O(log n)| O(n)       |
| `inorder()`   | O(n)    | O(n)       |
| `height()`    | O(n)    | O(n)       |
| `size()`      | O(1)    | O(1)       |

Worst case occurs when keys are inserted in sorted order,
producing a degenerate (linked-list) tree of height n − 1.

---

## Test Coverage

| Section                        | What it verifies                              |
|--------------------------------|-----------------------------------------------|
| Empty Tree                     | All operations safe on an empty tree          |
| Single Node                    | Insert, search, min/max, height = 0           |
| Insertions & Inorder Sort      | Inorder yields sorted output                  |
| Duplicate Handling             | Duplicate keys are silently ignored           |
| Delete — Leaf Node             | Leaf removal, size/inorder correct            |
| Delete — One Child             | Child is promoted correctly                   |
| Delete — Two Children          | In-order successor replaces deleted node      |
| Delete — Root                  | Tree becomes empty correctly                  |
| Delete — Non-existent Key      | No crash, tree unchanged                      |
| Sequential Insert              | Worst-case (skewed) height = n − 1            |
| Large Random Dataset           | 100-node insert + 50-node mass delete         |