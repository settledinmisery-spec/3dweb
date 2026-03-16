#include "mime_type.h"
#include <string.h>
#include <strings.h>

// Helper to determine MIME type based on extension
const char* get_mime_type(const char *path) {
	const char *ext = strrchr(path, '.');
	if (!ext) return "application/octet-stream";

	if (strcasecmp(ext, ".html") == 0) return "text/html";
	if (strcasecmp(ext, ".htm") == 0) return "text/html";
	if (strcasecmp(ext, ".css") == 0) return "text/css";
	if (strcasecmp(ext, ".js") == 0) return "application/javascript";
	if (strcasecmp(ext, ".json") == 0) return "application/json";
	if (strcasecmp(ext, ".png") == 0) return "image/png";
	if (strcasecmp(ext, ".jpg") == 0) return "image/jpeg";
	if (strcasecmp(ext, ".jpeg") == 0) return "image/jpeg";
	if (strcasecmp(ext, ".gif") == 0) return "image/gif";
	if (strcasecmp(ext, ".webp") == 0) return "image/webp";
	if (strcasecmp(ext, ".ico") == 0) return "image/x-icon";
	if (strcasecmp(ext, ".txt") == 0) return "text/plain";
	if (strcasecmp(ext, ".xml") == 0) return "text/xml";
	if (strcasecmp(ext, ".pdf") == 0) return "application/pdf";
	
	// Additional Images
	if (strcasecmp(ext, ".svg") == 0) return "image/svg+xml";
	if (strcasecmp(ext, ".bmp") == 0) return "image/bmp";
	if (strcasecmp(ext, ".tiff") == 0) return "image/tiff";
	if (strcasecmp(ext, ".tif") == 0) return "image/tiff";

	// Additional Text / Documents
	if (strcasecmp(ext, ".csv") == 0) return "text/csv";
	if (strcasecmp(ext, ".md") == 0) return "text/markdown";
	if (strcasecmp(ext, ".rtf") == 0) return "application/rtf";

	// Archives
	if (strcasecmp(ext, ".zip") == 0) return "application/zip";
	if (strcasecmp(ext, ".tar") == 0) return "application/x-tar";
	if (strcasecmp(ext, ".gz") == 0) return "application/gzip";
	if (strcasecmp(ext, ".bz2") == 0) return "application/x-bzip2";
	if (strcasecmp(ext, ".7z") == 0) return "application/x-7z-compressed";
	if (strcasecmp(ext, ".rar") == 0) return "application/vnd.rar";

	// Fonts
	if (strcasecmp(ext, ".woff") == 0) return "font/woff";
	if (strcasecmp(ext, ".woff2") == 0) return "font/woff2";
	if (strcasecmp(ext, ".ttf") == 0) return "font/ttf";
	if (strcasecmp(ext, ".otf") == 0) return "font/otf";
	if (strcasecmp(ext, ".eot") == 0) return "application/vnd.ms-fontobject";

	// Web / Other
	if (strcasecmp(ext, ".wasm") == 0) return "application/wasm";

	// Audio types
	if (strcasecmp(ext, ".ogg") == 0) return "audio/ogg";
	if (strcasecmp(ext, ".m4a") == 0) return "audio/mp4";
	if (strcasecmp(ext, ".flac") == 0) return "audio/flac";
	if (strcasecmp(ext, ".mp3") == 0) return "audio/mpeg";
	if (strcasecmp(ext, ".wav") == 0) return "audio/wav";
	
	// Video types
	if (strcasecmp(ext, ".mp4") == 0) return "video/mp4";
	if (strcasecmp(ext, ".webm") == 0) return "video/webm";
	if (strcasecmp(ext, ".mkv") == 0) return "video/x-matroska";

	return "application/octet-stream";
}
