package main

import (
    "fmt"
    "log"
    "net/http"
    "go-http-server/handler"
)

func main() {
    port := ":2020"
    fmt.Println("Server running on port", port)

    http.HandleFunc("/", handler.HandleRequest)

    if err := http.ListenAndServe(port, nil); err != nil {
        log.Fatal("Server failed:", err)
    }
}
