#include "template.h"

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

bool file_exists(const char *path) { return access(path, F_OK) == 0; };

const char *extract_language_from_name(const char *templateName) {
  static char extension[64] = "";
  const char *underscore = strchr(templateName, '_');
  if (underscore != NULL) {
    size_t langLen = underscore - templateName;
    if (langLen < sizeof(extension)) {
      strncpy(extension, templateName, langLen);
      extension[langLen] = '\0';
    }
  }

  return extension;
}

void create_filename(char *outFile, size_t size, const char *filename,
                     const char *ext) {
  if (strlen(ext) > 0)
    snprintf(outFile, size, "%s.%s", filename, ext);
  else
    snprintf(outFile, size, "%s", filename);
}

void copy_template_content(FILE *templateFile, FILE *newFile,
                           const char *filename) {
  char line[1024];
  while (fgets(line, sizeof(line), templateFile)) {
    char *pos = strstr(line, "{FUNCTION_NAME}");
    if (pos) {
      char newLine[1024];
      *pos = '\0';
      snprintf(newLine, sizeof(newLine), "%s%s%s", line, filename,
               pos + strlen("{FUNCTION_NAME}"));
      fputs(newLine, newFile);
    } else {
      fputs(line, newFile);
    }
  }
}

void create_template(const char *language, const char *templateName) {
  mkdir(".templates", 0700);

  char path[512];
  snprintf(path, sizeof(path), ".templates/%s_%s.tmpl", language, templateName);

  if (file_exists(path)) {
    printf("Error: template '%s_%s' already exists.\n", language, templateName);
    return;
  }

  FILE *f = fopen(path, "w");
  if (!f) {
    perror("Error creating template");
    return;
  }

  fprintf(f, "// Template: %s_%s\n", language, templateName);
  fprintf(f, "// Add your boilerplate and placeholders here\n");
  fprintf(f,
          "// The file name will be used as your function name by default: "
          "{FUNCTION_NAME}\n");

  fclose(f);
  printf("Template '%s_%s' created at %s\n", language, templateName, path);
}

void create_file_from_template(const char *filename, const char *templateName) {
  char templatePath[512];
  snprintf(templatePath, sizeof(templatePath), ".templates/%s.tmpl",
           templateName);

  if (!file_exists(templatePath)) {
    printf("Error: template '%s' not found.\n", templateName);
    return;
  }

  // extract language (everything before '_') 
  const char *ext = extract_language_from_name(templateName);

  // build output file name with proper extension
  char outFile[512];
  create_filename(outFile, sizeof(outFile), filename, ext);

  // open template and new file 
  FILE *templateFile = fopen(templatePath, "r");
  if (!templateFile) {
    perror("Error opening template");
    return;
  }

  FILE *newFile = fopen(outFile, "w");
  if (!newFile) {
    perror("Error creating new file");
    fclose(templateFile);
    return;
  }

  // copy template content
  copy_template_content(templateFile, newFile, templateName);

  fclose(templateFile);
  fclose(newFile);

  printf("Created file: %s\n", outFile);
}

void list_templates() {
  DIR *dir = opendir(".templates");
  if (!dir) {
    perror("Error opening .templates");
    return;
  }

  struct dirent *entry;
  printf("Templates:\n");
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.') continue;  // skips '.'
    printf("  %s\n", entry->d_name);
  }
}