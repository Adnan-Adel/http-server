package handler

import (
    "fmt"
    "io/ioutil"
    "net/http"
    "strings"

    "go-http-server/utils"
    "go-http-server/error"
)

func HandleRequest(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodGet {
        error.Send405(w)
        return
    }

    path := r.URL.Path
    if path == "/" {
        path = "index.html"
    } else {
        path = strings.TrimPrefix(path, "/")
    }

    data, err := ioutil.ReadFile(path)
    if err != nil {
        error.Send404(w)
        return
    }

    contentType := utils.GetMimeType(path)

    w.Header().Set("Content-Type", contentType)
    w.Header().Set("Content-Length", fmt.Sprintf("%d", len(data)))
    w.WriteHeader(http.StatusOK)
    w.Write(data)
}
