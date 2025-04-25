package error

import (
    "net/http"
)

func Send404(w http.ResponseWriter) {
    w.WriteHeader(http.StatusNotFound)
    w.Write([]byte("<h1>404 Not Found</h1>"))
}

func Send405(w http.ResponseWriter) {
    w.WriteHeader(http.StatusMethodNotAllowed)
    w.Write([]byte("<h1>405 Method Not Allowed</h1>"))
}
