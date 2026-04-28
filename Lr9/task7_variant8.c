#include <stdio.h>
#include <stdlib.h>

int main() {
printf("Variant 8\n");
printf("Creating a user group with full access to a specific directory.\n\n");

printf("Executing commands:\n\n");

system("sudo groupadd labgroup 2>/dev/null");
system("sudo mkdir -p /tmp/group_dir");
system("sudo chown root:labgroup /tmp/group_dir");
system("sudo chmod 770 /tmp/group_dir");

printf("Directory created: /temp/group_dir\n\n");

printf("Permissions:\n");
system("ls -ld /tmp/group_dir");

printf("\nTo add the current user to the group, run:\n");
printf("sudo usermod -aG labgroup $XUSER\n");
printf("newgrp labgroup\n");

printf("\nAfter that, you can test:\n");
printf("touch /tmp/group_dir/text.txt\n");
printf("ls -l /tmp/group_dir\n");

return 0;
}
