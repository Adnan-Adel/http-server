# 🚀 Go HTTP Server

A lightweight and multithreaded HTTP server written in **Go** that serves static files like `.html`, `.css`, `.js`, `.png`, and more — perfect for learning how servers work or hosting a simple static website.

---

## 🌐 Features

- ✅ Serves static files (HTML, CSS, JS, Images)
- 🧠 Automatically sets correct **MIME type**
- ⚙️ Handles **404 Not Found** and **405 Method Not Allowed**
- 🧵 Built-in **concurrency** using goroutines
- 📦 Modular design using Go packages
- 💡 Easy to extend and customize

---

## 🧱 Project Structure

```
go-http-server/
├── main.go
├── index.html          ← Static file (required)
├── handler/
│   └── request_handler.go
├── utils/
│   └── mime.go
└── error/
    └── response.go
```

> **Note:** Currently, the server serves files from the project root.

---

## 📥 Getting Started

### 🔧 Prerequisites

- [Go](https://golang.org/dl/) installed (version 1.16 or above recommended)

### 📦 Clone the Project

```bash
git clone https://github.com/yourusername/go-http-server.git
cd go-http-server
```

### ⚙️ Initialize Go Module

```bash
go mod init go-http-server
```

---

## 🧪 Example `index.html`

Create a simple `index.html` file in the root directory:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Go HTTP Server</title>
</head>
<body>
    <h1>🚀 Hello from Go!</h1>
    <p>This is served by your Go HTTP server.</p>
</body>
</html>
```

---

## ▶️ Run the Server

```bash
go run main.go
```

Visit [http://localhost:2020](http://localhost:2020) in your browser.

---

## 📂 Serving Static Files

- Drop files like `style.css`, `script.js`, or images into the project root.
- Access them via URL like:
  - [http://localhost:2020/style.css](http://localhost:2020/style.css)
  - [http://localhost:2020/image.png](http://localhost:2020/image.png)

---

## 🧠 How It Works

- Uses Go’s `net/http` package for handling connections.
- `handler.HandleRequest` serves content or responds with appropriate error.
- `utils.GetMimeType()` maps file extensions to content types.
- Errors like 404 and 405 are handled by simple functions in `error/response.go`.

---

## 🧰 Available MIME Types

| Extension       | MIME Type                |
|------------------|--------------------------|
| `.html`         | `text/html`              |
| `.css`          | `text/css`               |
| `.js`           | `application/javascript` |
| `.png`          | `image/png`              |
| `.jpg`, `.jpeg` | `image/jpeg`             |
| `.gif`          | `image/gif`              |
| *(others)*      | `application/octet-stream` (default) |

---

## 🚧 Planned Improvements

- [ ] Serve files from `public/` or `static/` directory
- [ ] Add logging middleware
- [ ] Add CLI flags for port and directory
- [ ] Serve `index.html` by default for directories
- [ ] Add request logging with timestamps

---

## 🛠 Troubleshooting

- **Nothing loads in browser**  
  Ensure the server is running and you’ve added an `index.html` file.

- **Changes not showing up?**  
  Try clearing browser cache or restart the server.

---

## 🤝 Contributing

Pull requests and suggestions are welcome! Feel free to fork the project and submit a PR.

---

## 📄 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
