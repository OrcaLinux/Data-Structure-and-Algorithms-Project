# XML Visualization and Analysis Tool

This project aims to develop a GUI-based program to parse, visualize, and analyze XML files representing users in a social network. The tool is currently under refactoring, and the current implementation may not fully align with the intended functionality. We appreciate your understanding as we work to enhance the tool's features and reliability.

## Table of Contents
- [Introduction](#introduction)
- [Current Status](#current-status)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

XML (Extensible Markup Language) serves as a fundamental format for data exchange among devices. This project targets the development of a robust GUI program capable of handling XML files representing social network users. By parsing and visualizing this data, the tool offers insights into network structures and supports various transformations of the XML content.

## Current Status

**This project is under active development and refactoring.**  
- The current implementation might not fully meet the described features and requirements.
- We are actively reorganizing the project structure, optimizing code, and ensuring feature alignment with the project's goals.

If you wish to contribute during this phase, please refer to the [Contributing](#contributing) section.

## Features

### Level 1 Requirements
- **XML Consistency Check:** Detects and resolves inconsistencies in XML files.
- **XML Formatting:** Ensures well-formatted XML through indentation.
- **XML to JSON Conversion:** Transforms XML data into JSON format.
- **XML Minification:** Reduces file size by removing whitespaces and newlines.
- **Data Compression:** Implements an ad-hoc compression technique for file size reduction.
- **Graph Representation:** Utilizes a graph data structure to depict user relations within the network.

### Level 2 Requirements
- **Network Analysis:** Identifies influential and active users, mutual followers, and suggests users to follow.
- **Post Search:** Enables searching for specific words/topics within posts.
- **Graph Visualization:** Utilizes third-party libraries/tools for visualizing the network graph.
- **Undo/Redo Operations:** Implements functionality for reverting or reapplying changes made during editing.

## Project Structure

The project is structured as follows (subject to change during refactoring):
- `/src`: Contains source code files for the program.
- `/data`: Sample XML files for testing and development.
- `/docs`: Documentation and diagrams describing implementation details and project insights.

## Requirements

The project requires the implementation of various data structures, including arrays, linked lists, stacks, queues, and priority queues (heap). Additionally, an in-house implementation of one data structure is mandatory. The usage of GitHub/GitLab for project management and version control is required.

## Usage

Currently, the program may not function as expected due to ongoing development and refactoring. Once development stabilizes, detailed usage instructions will be provided.

## Contributing

We welcome contributions to enhance this project, especially during this development phase. Feel free to submit issues or pull requests, and ensure that they align with the ongoing reorganization.

## License

This project is licensed under the [MIT](link).
