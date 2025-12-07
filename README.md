# Smart City Project

## Overview
Semester project for Data Structures course, modeling Islamabad as a smart city using C++ data structures. Console-based app (optional SFML for visuals) simulating transport, education, medical, commercial, public facilities, and population sectors.

## Features
### Core Modules
- **Transport (Graph)**: Register buses/companies, add stops/edges, shortest paths (Dijkstra), nearest bus search, hash lookups.
- **Education (Tree + Hash)**: School hierarchy, registrations, subject searches, rankings (priority queue), nearest school.
- **Medical (Hash + Graph + Priority Queue)**: Hospitals/pharmacies, specializations, emergency beds (max-heap), medicine searches, nearest lookups.
- **Commercial (Mall)**: Product registration (hash), nearest mall, category search.
- **Public Facilities**: Add/search mosques, parks, etc., as graph nodes.
- **Population & Housing (Tree + Hash)**: Citizen data by CNIC, reports (age, density, occupation, gender).

### Bonus Modules
- School bus tracking, airport/rail integration, real-time simulation, emergency routing, population heatmap.

### Data Structures
- Graphs: Adjacency list, weighted, Dijkstra.
- Trees: N-ary for hierarchy, 3-level for schools, general for families.
- Hash Tables: Separate chaining, manual hash (polynomial/modular).
- Priority Queue: Binary min-heap.
- Linked List: Singly for bus routes.
- Queue: Circular for passengers.
- Stack: For route history.

Uses sample dataset; dynamic data addition.

## Requirements
- C++.
- Visual Studio 2022/2026.
- SFML (pre-configured).

## Installation
1. `git clone <repo-url>`
2. Open the solution file in Visual Studio.
3. Build (Debug/Release).

## How to Run
- Run executable via VS (F5) or from output folder.
- Menu-driven console interface.
- Optional SFML windows for visuals.

## Usage Notes
- Menu for interactions (e.g., paths, searches).
- Complexity: O(1) avg lookups, O(E log V) paths.
- See Report.pdf for DS details.

## Contributors
- Muhammad Bilal
- Asad Ullah Kamil
- Syed Moin ud Din

## Notes
Encourages creativity; added bonus features.

"Remember - We believe in you!"
