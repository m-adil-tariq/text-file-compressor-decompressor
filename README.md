# Huffman File Compressor & Decompressor

A custom **Text File Compressor and Decompressor** written in C++ using the **Huffman Coding algorithm** — a classic data compression technique that reduces file size by assigning variable-length binary codes to characters based on their frequency.

What makes this implementation distinct: **no STL is used**. All foundational data structures — including a custom Linked List and a Binary Tree-based Min-Heap — are built entirely from scratch.

---

## How It Works
<img width="540" height="302" alt="ds-project-1054_bNlNl3Pp" src="https://github.com/user-attachments/assets/24d7a50b-2aa3-40c5-adf1-3a4b050f160b" />

**Please wait a few seconds, the demo GIF is loading...**

### Compression

1. **Frequency Counting** — The input `.txt` file is read character by character, building a linked list of unique characters and their occurrence counts
2. **Min-Heap Construction** — Each unique character and its frequency is wrapped in a `HeapNode` and inserted into a dynamic Min-Heap, keeping the lowest-frequency node at the top
3. **Huffman Tree Building** — The two lowest-frequency nodes are repeatedly extracted, merged into a new internal node, and reinserted until a single root node remains
4. **Code Generation** — The tree is traversed to assign binary codes: going left adds a `0`, going right adds a `1`. Frequent characters get short codes (e.g. `10`), rare ones get longer codes (e.g. `01101`)
5. **Bit Packing** — Characters in the original text are replaced by their binary codes, packed into 8-bit bytes, and written to a `.bin` output file along with a metadata header

### Decompression

1. **Tree Reconstruction** — The metadata header in the `.bin` file is read to recreate the exact Huffman Tree used during compression
2. **Bitstream Decoding** — The compressed bitstream is read byte by byte. Starting from the root, a `0` bit moves left and a `1` bit moves right. When a leaf node (character) is reached, it is written to the output file and the pointer resets to root

---

## Compressed File Format

Every `.bin` file produced has this header structure prepended before the actual data:

| Section | Format | Description |
|---|---|---|
| Tree Structure | Recursive Bit/Char Stream | Serialized Huffman Tree — `0` = internal node, `1` + `char` = leaf node |
| Tree Delimiter | `char` (`#`) | Marks the end of the tree data |
| Original Length | `long long` (8 bytes) | Character count of the original file — prevents padding bits from being decoded as data |
| Compressed Bitstream | Binary Bytes | Actual encoded text packed into 8-bit blocks |

---

## Expected Compression Ratios

Performance depends on the **entropy** of the input file:

| Input Type | Expected Reduction |
|---|---|
| Standard English text / source code | 30% – 50% |
| Highly repetitive text | 70%+ |
| Very small files (< 1 KB) or high-diversity text | May be larger than original* |

> *On small files, the overhead of storing the Huffman Tree in the header can outweigh the savings from encoding.

---

## Getting Started

### Prerequisites

- A C++ compiler (g++ recommended)
- Any OS with a terminal


## Concepts Demonstrated

- Huffman Coding algorithm
- Custom Min-Heap (no STL `priority_queue`)
- Custom Linked List (no STL `list` or `map`)
- Binary Tree traversal and serialization
- Bitwise operations and bit packing
- File I/O in binary mode
