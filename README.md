# Text Extraction Tool for Windows 🪟
This project provides a tool for extracting text from various file formats on Windows machines. The tool is designed to be simple and easy to use, with a user-friendly interface that allows you to select the files you want to extract text from and save the results to a text file.

## Get started 🌾

To use this tool, you will need a Windows machine with the .NET Framework 4.5 or later installed. You can download the latest version of the .NET Framework from the Microsoft website.

You also need C++ installed
Plus, You have to install Visual studio 2022 which will be use to install desktop development with C++ workload, then install window SDK 10.0.22621 inside that workload

To get started with the tool, follow these steps:
1. Download the latest release of the tool from the project's GitHub repository.
2. Extract the contents of the zip file to a folder on your computer.
3. Open the extracted folder and run the TextExtractionTool.exe file.
4. Select the files you want to extract text from by clicking the "Select Files" button and browsing to the files on your computer.
5. Choose a location to save the extracted text file by clicking the "Select Output Folder" button and selecting a folder on your computer.
6. Click the "Extract Text" button to begin the text extraction process.

The tool will extract the text from the selected files and save the results to a text file in the output folder you specified.

That's all you need. 😉

## Supported File Formats
The tool supports the following file formats for text extraction:

<!-- Microsoft Word (.doc and .docx)
Microsoft Excel (.xls and .xlsx)
Microsoft PowerPoint (.ppt and .pptx)
Adobe PDF (.pdf) -->
Plain Text (.txt)
Images (ipg, png)


## Contributing
If you would like to contribute to this project, you can do so by submitting a pull request on the GitHub repository. Please include a detailed description of your changes and any relevant test cases.

<!-- ### Continuous Integration

- The configured workflow will check the types for each push and PR.
- The configured workflow will check the code style for each push and PR.
- **Automatic tests**
  used [Vitest ![Vitest version](https://img.shields.io/github/package-json/dependency-version/cawa-93/vite-electron-builder/dev/vitest?label=%20&color=yellow)][vitest]
  -- A blazing fast test framework powered by Vite.
  - Unit tests are placed within each package and are ran separately.
  - End-to-end tests are placed in the root [`tests`](tests) directory and use [playwright].

![Workflow graph](https://user-images.githubusercontent.com/1662812/213429323-ef4bcc87-c273-4f2f-b77f-c04cf6dbc36d.png)


### Publishing

- Each time you push changes to the `main` branch, the [`release`](.github/workflows/release.yml) workflow starts, which creates a new draft release. For each next commit will be created and replaced artifacts. That way you will always have draft with latest artifacts, and the release can be published once it is ready. 
  - Code signing supported. See [`release` workflow](.github/workflows/release.yml).
  - **Auto-update is supported**. After the release is published, all client applications will download the new version
  and install updates silently.
  
> **Note**:
> This template **configured only for GitHub public repository**, but electron-builder also supports other update distribution servers. Find more in [electron-builder docs](https://www.electron.build/configuration/publish). -->
