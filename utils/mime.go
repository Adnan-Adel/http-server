package utils

import "strings"

func GetMimeType(path string) string {
    switch {
    case strings.HasSuffix(path, ".html"):
        return "text/html"
    case strings.HasSuffix(path, ".css"):
        return "text/css"
    case strings.HasSuffix(path, ".js"):
        return "application/javascript"
    case strings.HasSuffix(path, ".png"):
        return "image/png"
    case strings.HasSuffix(path, ".jpg"), strings.HasSuffix(path, ".jpeg"):
        return "image/jpeg"
    case strings.HasSuffix(path, ".gif"):
        return "image/gif"
    default:
        return "application/octet-stream"
    }
}
