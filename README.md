# README for Practice 2 – Design of a Symmetric Encryption Algorithm

**Course**: TC-2007b - Integration of Computer Security in Networks and Software Systems  
**Practice Title**: Design of a Symmetric Encryption Algorithm

## Overview
In this practice, the goal is to design, implement, and test a symmetric encryption algorithm. Symmetric encryption is central to modern security systems, making this practice crucial for understanding the basics of cryptographic design. The practice involves incorporating techniques such as diffusion and confusion to ensure robust encryption.

## Learning Objectives
- Understand and apply techniques for generating **diffusion** in symmetric encryption algorithms.
- Understand and apply techniques for generating **confusion** in symmetric encryption algorithms.
- Design a symmetric encryption algorithm that incorporates both diffusion and confusion.
- Implement and test the algorithm using a programming language.

## Tools and Software
- **Reference Material**: Books or notes on cryptographic algorithms.
- **Cryptool**: A tool for visualizing cryptographic processes (optional).
- **Programming Language**: C++ (or another language with bit-level manipulation support).

## Steps for Design and Implementation

### 1. Algorithm Design
- **Characteristics Discussion**: Collaborate to discuss the essential traits of a robust symmetric encryption algorithm. These include security, reversibility, and efficiency.
- **Operations for Diffusion and Confusion**: Identify the operations that will achieve diffusion (e.g., transposition, bit shifting) and confusion (e.g., substitution, XOR).

### 2. Design Considerations
- The encryption algorithm should include **bit-level operations** such as bit shifting, transposition, substitution, and XOR.
- Several **rounds of encryption** should be applied to strengthen security.
- Optional: Incorporate advanced operations (multiplications, key rotation) for additional complexity.

### 3. Implementation
- **Input**: The program accepts an alphanumeric string (up to 100 characters) and a symmetric key (up to 16 characters or 128 bits).
- **Output**: The program will generate encrypted text, which can then be decrypted back into the original text using the same key.
- Testing should ensure proper encryption and decryption functionality.

### 4. Presentation and Deliverables
- A **5-minute presentation** demonstrating the design and implementation of the encryption algorithm.
- The deliverable includes the algorithm design, the working program, and a **technical manual** explaining the implementation details.

## Evaluation Rubric
- **Algorithm Design**: 10/10
- **Functionality and Implementation**: 30/30
- **Diffusion Techniques**: 22/22
- **Confusion Techniques**: 22/22
- **Graphical Interface**: 10/10
- **Presentation**: 6/6

## Deliverables
- Symmetric encryption algorithm (with source code).
- Demonstration of correct functionality (evidence of encryption and decryption).
- A technical manual detailing the design and workings of the encryption algorithm.
