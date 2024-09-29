#include "main.h"

#define USER_INFO_DIR "./user_information"  // 定义用户信息文件的存储目录
#define USER_CREDENTIALS_FILE USER_INFO_DIR "/user_credentials.txt"
#define TEMP_CREDENTIALS_FILE USER_INFO_DIR "/temp_credentials.txt"

// 检查并创建 user_information 文件夹
// 该函数在服务器启动时调用，确保 user_information 文件夹存在，如果不存在，则创建该文件夹
void check_and_create_user_information_dir() {
    struct stat st = {0};
    if (stat(USER_INFO_DIR, &st) == -1) {
        // 如果 user_information 文件夹不存在，则创建该目录
        mkdir(USER_INFO_DIR, 0700);  // 创建目录，权限为 0700（仅所有者可读写）
        log_message("user_information directory created.");
    }
}

// 检查用户名是否存在
int username_exists(const char *username) {
    FILE *file = fopen(USER_CREDENTIALS_FILE, "r");  // 从 user_credentials.txt 读取数据
    if (file == NULL) {
        return 0; // 文件不存在时，假定用户名不存在
    }

    char line[100];
    char stored_username[50];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s", stored_username);
        if (strcmp(username, stored_username) == 0) {
            fclose(file);
            return 1; // 用户名存在
        }
    }

    fclose(file);
    return 0; // 用户名不存在
}

// 注册新账号
int register_account(const char *username, const char *password) {
    if (username_exists(username)) {
        return 0; // 用户名已存在
    }

    FILE *file = fopen(USER_CREDENTIALS_FILE, "a");  // 以追加模式打开文件
    if (file == NULL) {
        return 0; // 打开文件失败
    }

    fprintf(file, "%s %s\n", username, password);  // 写入格式: 用户名 密码
    fclose(file);
    return 1; // 注册成功
}

// 验证登录
int validate_login(const char *username, const char *password)
{
    FILE *file = fopen(USER_CREDENTIALS_FILE, "r");  // 从 user_credentials.txt 读取数据
    if (file == NULL)
    {
        return 0;
    }
    char line[100];
    char stored_username[50], stored_password[50];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s %s", stored_username, stored_password);
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0)
        {
            printf("登陆成功\n");
            fclose(file);
            return 1; // 验证成功
        }
    }

    fclose(file);
    return 0; // 验证失败
}

// 注销账号
int delete_account(const char *username, const char *password) {
    FILE *file = fopen(USER_CREDENTIALS_FILE, "r");
    FILE *temp_file = fopen(TEMP_CREDENTIALS_FILE, "w");
    if (file == NULL || temp_file == NULL) {
        return 0; // 错误处理
    }

    char line[100];
    char stored_username[50], stored_password[50];
    int found = 0;

    // 遍历文件并删除匹配的用户
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s", stored_username, stored_password);
        if (strcmp(username, stored_username) != 0) {
            fprintf(temp_file, "%s", line); // 只保留不匹配的行
        } else {
            found = 1; // 找到并删除
        }
    }

    fclose(file);
    fclose(temp_file);

    // 删除旧文件并重命名临时文件
    remove(USER_CREDENTIALS_FILE);
    rename(TEMP_CREDENTIALS_FILE, USER_CREDENTIALS_FILE);
    
    return found; // 返回是否找到并删除
}

