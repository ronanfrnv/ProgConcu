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

