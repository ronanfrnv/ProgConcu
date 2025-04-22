## A Retenir 
En C, les fonctions `puts` et `printf` servent toutes deux à afficher du texte à l'écran, mais elles ont des différences importantes en termes de comportement et d'utilisation :

---

### 🔹 `puts` :
- **Utilité** : Affiche une chaîne de caractères suivie **automatiquement** d’un saut de ligne (`\n`).
- **Syntaxe** : `puts("Bonjour");`
- **Comportement** : Affiche `Bonjour\n`
- **Limitation** : N'accepte **que** des chaînes de caractères (`char*`). Impossible de formater comme avec `printf`.

**Exemple** :
```c
puts("Hello world");
```
➡ Affiche :
```
Hello world
```

---

### 🔹 `printf` :
- **Utilité** : Fonction d’affichage **formaté**. Permet d’insérer des variables dans le texte, et de choisir leur format (entiers, flottants, chaînes, etc.).
- **Syntaxe** : `printf("Valeur : %d", 42);`
- **Comportement** : Ne rajoute **pas automatiquement** de saut de ligne.
- **Flexibilité** : Très polyvalent, permet le formatage précis.

**Exemple** :
```c
printf("Hello world\n");
```
➡ Affiche la même chose que `puts`, mais ici tu dois mettre `\n` manuellement.

---

### ✅ En résumé :

| Fonction | Saut de ligne automatique | Formatage possible | Usage typique |
|---------|---------------------------|--------------------|----------------|
| `puts`  | Oui                        | Non                | Affichage simple |
| `printf`| Non                        | Oui                | Affichage complexe |

### Options de compilations

-Wall: Ajout de warning classique
-Wextra: Ajout de warning supplémentaire
-g: Ajout des informations de debug au sein de l’exécutable
-o: Nom de l’exécutable
---

### 💾 **Qu’est-ce qu’un *programme* ?**
Un **programme** est un **fichier** contenant du code exécutable — un ensemble d’instructions **stockées sur un disque**.

- 📂 Il est **passif** : ce n’est que du code en attente d’exécution.
- ✍️ Il peut être écrit en C, Python, Java, etc.
- 📦 Il contient les instructions, les données statiques, éventuellement des ressources (images, sons...).

🧠 **Exemple** :
```c
int main() {
    printf("Bonjour");
    return 0;
}
```
➡ Ce fichier source compilé devient un **programme exécutable** (ex: `bonjour.exe` sous Windows, ou `./bonjour` sous Linux).

---

### 🧠 **Qu’est-ce qu’un *processus* ?**
Un **processus** est une **instance d’un programme en cours d’exécution**.

- 🚀 Il est **actif** : il a une vie, une exécution.
- 🧮 Il dispose de sa **mémoire** propre (pile, tas, code), d’un **PID** (Process ID), et tourne sous le contrôle du système d’exploitation.
- 🔁 Un même programme peut avoir **plusieurs processus** actifs (si on l’exécute plusieurs fois).

🧠 **Exemple** :
Tu ouvres deux fois Google Chrome → tu as **plusieurs processus**, mais **un seul programme**.

---
Parfait, tu touches là au **cœur de la programmation système sous Unix/Linux**. Détaillons ça étape par étape en simplifiant :

---

### 🧩 Prototype de `fork`
```c
pid_t fork(void);
```
- `pid_t` est un type pour représenter un **identifiant de processus (PID)**.
- `fork()` est une fonction système qui **crée un nouveau processus**, **copie exacte du processus courant**.

---

### ⚙️ Que fait `fork()` ?
Quand tu appelles `fork()`, **le processus courant est dupliqué** :
- Un nouveau processus (appelé **fils**) est créé.
- Le processus d'origine (appelé **père**) continue d’exister.
- Le fils est **presque une copie conforme du père** : même code, même variables (au moment du fork), mêmes fichiers ouverts.

Mais :
- Chaque processus a **son propre espace mémoire** (ils ne partagent pas les variables).
- Le **PID** du fils est **différent**.
- Les **descripteurs de fichiers** sont dupliqués (donc les deux peuvent lire/écrire les mêmes fichiers si non modifié).

---

### 🔁 Que retourne `fork()` ?
Le retour de `fork()` permet de **distinguer qui est le père et qui est le fils** :

| Contexte         | Valeur retournée par `fork()` |
|------------------|-------------------------------|
| Processus père   | **PID du processus fils**     |
| Processus fils   | **0**                         |
| Erreur (échec)   | **-1**                        |

---

### 🔍 Exemple :
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork échoué");
        return 1;
    }
    if (pid == 0) {
        printf("Je suis le fils, mon PID = %d\n", getpid());
    } else {
        printf("Je suis le père, mon PID = %d, mon fils a le PID = %d\n", getpid(), pid);
    }

    return 0;
}
```

---

### 🔄 Ce qui se passe à l’exécution :
- `fork()` est appelé → le système duplique le processus.
- Le **père** continue l’exécution **après le fork**, avec `pid > 0`.
- Le **fils** commence **au même endroit**, mais `pid == 0`.
- Tu te retrouves avec **deux programmes quasi identiques** qui s’exécutent **indépendamment**.

---

### ❗ Cas d’erreur :
Si `fork()` retourne `-1`, cela signifie :
- Trop de processus créés (limite du système atteinte).
- Ressources insuffisantes pour allouer un nouveau processus.


---

## 🧩 1. **Comment un processus se termine ?**

Un **processus** (= programme en cours d’exécution) se termine dans **3 cas principaux** :

### ✅ Fin normale :
- `return 0;` → dans le `main`, ça veut dire "tout s'est bien passé".
- `exit(0);` → peut être utilisé **n'importe où** dans le programme pour dire "je quitte proprement".

### ❌ Fin avec erreur :
- `exit(1);`, `exit(42);` → tout ce qui n’est pas 0 indique une **erreur**.
- C’est à toi (le programmeur) de décider ce que ces valeurs veulent dire.

📘 **Exemple** :
```c
if (fichierIntrouvable) {
    exit(1); // Erreur : fichier manquant
}
```

---

## 🧟‍♂️ 2. **C’est quoi un processus zombie ?**

Quand un **processus se termine**, il ne disparaît **pas tout de suite**.

🔍 Il devient un **zombie** 👻 s’il a encore un **père vivant** qui **n’a pas récupéré son état**.

Un zombie :
- Ne travaille plus.
- Mais **reste en mémoire** temporairement, pour que le père puisse **savoir comment il est mort**.

🧠 Pourquoi ?
👉 Le système d’exploitation garde **le status de fin** (erreur ou succès) pour que le père puisse le lire.

---

## 🧭 3. **Comment le père "récupère" un fils zombie ?**

Il utilise la fonction :

```c
pid_t wait(int *status);
```

🔧 Ce que ça fait :
- Il **attend qu’un fils se termine** (si ce n’est pas déjà fait).
- Il **remplit `status`** avec le code de sortie du fils (0 = OK, autre = erreur).
- Il **renvoie le PID du fils terminé**.

👉 Une fois que c’est fait, le **fils est totalement supprimé de la mémoire** → il **n’est plus zombie**.

---

## 🧪 Exemple simple avec `wait()` :
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Fils
        printf("Fils: je me termine avec exit(0).\n");
        exit(0);
    } else {
        // Père
        int status;
        pid_t child_pid = wait(&status);
        printf("Père: mon fils %d est terminé avec le code %d\n", child_pid, WEXITSTATUS(status));
    }

    return 0;
}
```

---

## 🧾 En résumé simple :

| Action | Explication |
|--------|-------------|
| `return 0;` ou `exit(0);` | Le processus dit "tout va bien" |
| `exit(x);` (x ≠ 0) | Le processus dit "j'ai eu un problème" |
| Zombie | Processus terminé mais pas encore "ramassé" par le père |
| `wait(&status);` | Le père attend et lit le résultat de fin du fils |

---

Tu veux que je t’illustre aussi ce qu’il se passe si on **n’utilise pas `wait()`** ou qu’on crée **plein de zombies** ?
