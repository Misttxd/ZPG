# CV5 – implementační plán

Pracovní projekt: `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG`.
Uspořádání projektu: `src` obsahuje všechny vlastní `.cpp`; `include` obsahuje všechny vlastní `.h` a `.hpp`, včetně modelových dat. Obě složky jsou bez podsložek.

Cílem je postupně doplnit kameru, propojit ji se shader programy přes Observer, procházet prostorovým lesem a zobrazit hodiny jedním draw callem. Tento soubor je plán; implementace zatím nebyla změněna. Při společné práci budeme dělat vždy jeden malý krok a ověřovat výsledek.

## Zadání a návaznost

Hlavní zdroj je [CV5.md](<C:/Users/Alkys/Documents/ZPG/RN Cvičení/CV5/CV5.md>), doplněný původními snímky a přiloženým modelem. Závazné pro tento plán:

- `Camera` obsahuje `viewMatrix` a `projectionMatrix`.
- Vertex shader používá pořadí `projectionMatrix * viewMatrix * modelMatrix * position`.
- Kamerou lze procházet scénu a rozhlížet se myší; úhly mají vhodné omezení.
- Perspektivní projekce reaguje na poměr stran okna; `near = 0.1`.
- Les obsahuje alespoň 74 stromů.
- Celé hodiny z přiloženého modelu se vykreslí jedním draw callem.
- Observer je závazný podle tvého požadavku; samotné zadání ho nabízí jako možnost.

[CV3 z portálu](<C:/Users/Alkys/Documents/ZPG/Kelvin/Zadání/CV3.md>) požadovalo také více než 10 keřů, slunce a podpis ve scénách. To zachováme. [CV4 z portálu](<C:/Users/Alkys/Documents/ZPG/Kelvin/Zadání/CV4.md>) vyžadovalo Composite a statické i dynamické transformace; současné transformace objektů zůstanou základem.

[Přednáška 4](<C:/Users/Alkys/Documents/ZPG/PŘEDNÁŠKY/ZPG_Prednaska_4.pdf>) je z roku 2025. Pro CV5 je použitelná: kamera a `lookAt` na stranách 7–11, perspektiva na straně 19, viewport na straně 22 a vazby tříd na stranách 23 a 30. Ukázky jsou místy jen rozpracované. Použijeme `glm::lookAt` s malým `l`, úhly v radiánech a `glm::radians` při zadávání FOV ve stupních. Znaménko pohybu vlevo/vpravo ověříme podle skutečného směru kamery, ne podle názvu ukázkové metody `toLeft`.

## Co už projekt má

| Soubor | Současný stav a důsledek |
| --- | --- |
| [camera.h](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/camera.h>) | Prázdná, zatím nepoužívaná kostra. Doplníme ji; název není potřeba měnit. Definice konstruktoru přesuneme do `.cpp`, aby hlavičku šlo použít z více souborů. |
| [right.vert](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/shaders/right.vert>) | Už obsahuje všechny tři matice i správné pořadí násobení. View a projection jsou zatím jednotkové. |
| [Scene.h](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/Scene.h>) a [Scene.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/Scene.cpp>) | Scéna vlastní objekty i shader programy. Doplníme vlastnictví volitelné kamery a registraci observerů. |
| [ShaderProgram.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/ShaderProgram.cpp>) | Umí nahrát matici a před nastavením uniformu aktivuje správný program. Využijeme existující metody. Implementace floatového uniformu je zakomentovaná. |
| [ForestScene.hpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/ForestScene.hpp>) | Má 11 stromů, 11 keřů a slunce, rozmístěné v XY se z = 0. Potřebuje nové prostorové rozmístění a měřítko. |
| [Application.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/Application.cpp>) a [Callbacks.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/Callbacks.cpp>) | Existuje `deltaTime`, předávání `Application*` callbackům a přepínání scén. Myš zatím jen vypisuje zprávy; resize mění jen viewport. |
| [SceneSignature.hpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/SceneSignature.hpp>) | Podpis používá `right.vert`. Jeho shader vynecháme z registrace ke kameře, aby podpis zůstal v rohu obrazovky. |
| [Model.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/Model.cpp>) | Podporuje různý počet floatů na vrchol, ale zpřístupňuje jen první dva atributy. Pro hodiny doplníme třetí atribut s RGB. |
| [DrawableObjectFactory.cpp](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/DrawableObjectFactory.cpp>) | Modely už sdílí mezi objekty. Pro 74 stromů nepotřebujeme nové VBO pro každý strom. |

## Navržené propojení přes Observer

`Scene` vlastní svou kameru a shader programy. Kameru vytvoříme v lese a ve scéně hodin před vytvářením jejich shaderů. Dosavadní ukázkové scény mohou pokračovat bez kamery a používat jednotkové view/projection.

Přidáme malé rozhraní `ICameraObserver` s metodou přijímající nové view a projection matice. `ShaderProgram` toto rozhraní implementuje. `Camera` eviduje nevlastní ukazatele na pozorovatele a nabízí přihlášení, odhlášení a oznámení změny.

Tok změny bude:

1. `Application` předá pohyb, otočení nebo nové rozměry aktivní kameře.
2. `Camera` přepočítá příslušnou matici a oznámí změnu observerům.
3. Každý přihlášený `ShaderProgram` nahraje matice přes existující `setUniform`.
4. `DrawableObject` při vykreslení dál nastavuje vlastní `modelMatrix`.

To řeší konkrétní problém: les používá několik shader programů a všechny musí vidět stejnou změnu kamery. Kamera přitom nemusí znát konkrétní třídu shaderu ani jednotlivé stromy. Předáním samotných matic se vyhneme obousměrnému ukládání `Camera*` a `ShaderProgram*`.

Pravidla zapojení:

- `Scene::addShaderProgram` dostane parametr `usesCamera`, standardně zapnutý. Registrace proběhne pouze tehdy, když scéna kameru má, a až po vytvoření shader programu.
- Přihlášení ihned odešle aktuální matice. Scéna musí být správná i před prvním pohybem.
- Podpis použije `usesCamera = false`; jeho jednotkové matice zůstanou zachované.
- Při `Scene::clear()` nejprve vyčistíme seznam observerů, potom objekty a potom shader programy. Kamera pozorovatele nevlastní a při svém zániku nic neoznamuje.
- Kameru deklarujeme před kontejnery shaderů a objektů. Přesuny `unique_ptr` ve vektoru nemění adresy samotných shader programů.
- Observer použije stávající `setUniform`, které volá `use()`. Následující vykreslení si již dnes aktivuje správný shader při nastavení `modelMatrix`.

## Postup po malých krocích

### 1. Dokončit třídu Camera

**Soubory:** existující `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/camera.h`, nový `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/src/Camera.cpp` a [ZPG.vcxproj](<C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/ZPG.vcxproj>).

**Cíl:** kamera má platný stav a umí spočítat obě matice, zatím bez ovládání.

- Výslovně inicializovat matice; doplnit pozici `eye`, směr `target`, vektor `up` a úhly `alpha`, `fi` podle zadání.
- Pohled počítat jako `glm::lookAt(eye, eye + target, up)`. `target` zde znamená směr, zatímco druhý argument `lookAt` je bod.
- Perspektivu počítat z rozměrů framebufferu. Počáteční volba: FOV 60°, near 0.1, far 100; FOV a far jsou naše nastavení podle ukázky.
- Zachovat vzorce pro směr ze zadání. `alpha` držet uvnitř intervalu `(0, pi)` s malým odstupem od pólů, `fi` cyklicky vracet do rozsahu jedné otáčky.
- Camera nepracuje s GLFW ani přímo s OpenGL. Nový `.cpp` zařadit do projektu, soubory případně také do `.filters`.

**Ověření:** projekt se přeloží a dosavadní scény fungují. Malou kontrolou ověřit konečné hodnoty matic, směr při zvolených úhlech a nenulovou vzdálenost near.

### 2. Zapojit Observer a vlastnictví kamery

**Soubory:** Camera, Scene a ShaderProgram z tabulky výše; nový `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/ICameraObserver.h`, dále `SceneSignature.hpp` a `ForestScene.hpp`.

**Cíl:** změna jedné kamery se dostane do všech potřebných shader programů.

- Implementovat malé rozhraní, seznam observerů, okamžitou synchronizaci při registraci a bezpečné odpojení při čištění scény.
- V `Scene` zavést volitelnou `unique_ptr<Camera>` a jednoduchou metodu pro její vytvoření a zpřístupnění.
- V lese vytvořit kameru před jeho shadery; nejprve lze ponechat jednotkové matice pro ověření propojení.
- Podpis nezaregistrovat. Ostatní dosavadní scény ponechat bez kamery.

**Ověření:** známá změna matice se projeví na stromech, keřích i slunci, podpis drží své místo. Nově přihlášený shader dostane stav ihned. Ukončení aplikace a vyčištění scény nevolá zaniklé observery.

### 3. Upravit les a zapnout statickou perspektivní kameru

**Soubor:** `ForestScene.hpp`.

**Cíl:** skutečný prostorový les je vidět z rozumné počáteční pozice.

- Oddělit počty stromů a keřů: alespoň 74 stromů, zachovat alespoň současných 11 keřů a slunce.
- Náhodné rozmístění převést do roviny XZ; výška je osa Y. Současné hodnoty pro obrazovkové souřadnice nelze jen převzít.
- Sladit měřítko modelů, velikost lesa a výšku kamery. Ponechat současné Composite transformace a sdílení modelů přes factory.
- Nastavit pohled a perspektivu tak, aby kamera byla před lesem nebo na jeho okraji a dívala se dovnitř.
- Volitelně přidat existující model `Ground` pro lepší orientaci; není to samostatný požadavek CV5.

**Ověření:** nejméně 74 stromů, různá hloubka rozmístění a čitelné měřítko. Stromy, keře a slunce používají stejnou kameru. Staré demonstrační scény i podpis se zobrazují dál.

### 4. Připojit změnu rozměrů

**Soubory:** Application, Callbacks a Camera; přepínání využije stávající `SceneManager`.

**Cíl:** po změně okna zůstane správný viewport i perspektiva.

- Použít framebuffer-size callback a skutečné pixelové rozměry framebufferu.
- Vedle `glViewport` předat nové rozměry aktivní kameře. Poměr stran počítat jako `float(width) / height`.
- Rozměry uchovávat v Application a aplikovat je také při prvním zobrazení a při přepnutí scény, aby se opravila i dříve neaktivní kamera.
- Při nulové šířce nebo výšce nepřepočítávat projekci; po obnovení okna ji aktualizovat.

**Ověření:** široké a vysoké okno, minimalizace/obnovení a přepnutí scény po resize. Perspektiva se aktualizuje přes Observer, bez deformace způsobené chybným poměrem stran.

### 5. Přidat WASD a rozhlížení myší

**Soubory:** Application, Callbacks a Camera.

**Cíl:** kamerou lze plynule procházet les.

- Držené WASD číst přes `glfwGetKey` v hlavním cyklu. Pohyb násobit rychlostí a `deltaTime`; callback kláves ponechat pro přepínání scén a Escape.
- Pro chůzi promítnout dopředný směr do XZ a zachovat výšku kamery. Kombinovaný směr normalizovat, aby diagonála nebyla rychlejší.
- Podle tvého požadavku se rozhlížet pouze při držení levého tlačítka myši (`GLFW_MOUSE_BUTTON_LEFT`). Po uvolnění tlačítka rozhlížení zastavit. Callback předá rozdíl souřadnic, kamera z něj upraví úhly.
- Kurzor ponechat viditelný a volný v režimu `GLFW_CURSOR_NORMAL`; nezamykat ho ani při spuštění, ani během rozhlížení.
- První polohu myši jen uložit; resetovat ji při začátku rozhlížení, přepnutí scény a návratu fokusu. Bez fokusu kamerou nehýbat.
- Pohyb předávat pouze aktivní scéně s kamerou. Camera stále nedostává `GLFWwindow*`.

**Ověření:** držení kláves funguje plynule, rychlost závisí na čase. Myš otáčí kamerou pouze při držení levého tlačítka, po uvolnění přestane a kurzor zůstává volný. Myš nezpůsobí první skok a pohled se nepřeklopí na pólech. Čísla, Tab a Escape dál fungují.

### 6. Načíst a staticky zobrazit celé hodiny

**Soubory:** Model, DrawableObjectFactory, Application a projekt; nové `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/clock.h`, `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/include/ClockScene.hpp` a shadery `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/shaders/clock.vert`, `C:/Users/Alkys/Documents/ZPG/RN Implementace/ZPG/shaders/clock.frag`.

**Cíl:** kompletní přiložený model je jeden DrawableObject, jeden VBO/VAO a jeden draw call.

- Použít [přiložený clock.h](<C:/Users/Alkys/Documents/ZPG/RN Cvičení/CV5/clock.h>). `clock.zip` obsahuje stejnou hlavičku, další implementace v něm není.
- Model má 44 826 vrcholů, každý s devíti floaty: pozice, normála, RGB.
- Stávající atributy 0/1 ponechat. Pro devítifloatové modely přidat atribut 2: RGB na offsetu `6 * sizeof(float)`. Shader hodin použije toto RGB, dosavadní shadery zůstanou funkční.
- Přidat `ObjectType::Clock` do factory. V ClockScene vytvořit kameru, jeden shader program hodin a jeden objekt hodin.
- Zobrazit čelo modelu správným natočením; čelní normály směřují k lokálnímu −Z.

**Ověření:** ciferník i všechny ručičky jsou čitelné. Celé hodiny se kreslí jediným `glDrawArrays` pro 44 826 vrcholů. Případný podpis je samostatný objekt; požadavek jednoho draw callu zde vztahujeme na celý model hodin.

### 7. Rozhýbat ručičky bez dalších draw callů

**Soubory:** ClockScene, shadery hodin, ShaderProgram a Scene.

**Cíl:** ručičky se otáčejí nezávisle, stále uvnitř jediného vykreslení hodin.

- RGB v modelu použít jako identifikaci části: červená `(1,0,0)` sekundová ručička, zelená `(0,1,0)` minutová, modrá `(0,0,1)` hodinová. Ostatní části zůstanou statické. Rozdělení podle rozsahů vrcholů by bylo křehké, protože části jsou v datech na více místech.
- Vertex shader podle identifikace vybere lokální rotaci kolem Z a pivotu ručiček u počátku. Výsledné pořadí je `P * V * M * R * position`.
- Doplnit již deklarované `setUniform(name, float)` a posílat jeden údaj času. Úhly spočítat v shaderu podle period 60 s, 3 600 s a 43 200 s. Směr i počáteční natočení ověřit pohledem na čelo hodin.
- Změnit `Scene::update` na virtuální a zpřístupnit stávající čas chráněným getterem. `ClockScene::update` zavolá základní update a poté nastaví časový uniform; nevytvářet druhý nezávislý časovač.
- Identifikační RGB lze pro výsledný vzhled přemapovat: sekundová červená, minutová a hodinová černé. Ostatní barvy sladit s referenčním obrázkem.

**Rozlišení zadání a volby:** text požaduje hodiny a jeden draw call, výslovně neurčuje animaci ani skutečný systémový čas. Animace je naše rozumná implementační volba; začneme časem od spuštění scény. Skutečný čas nebo přepínání rychlosti lze přidat později.

**Ověření:** časy 0, 15, 30 a 60 sekund ukážou správné natočení sekundové ručičky; delší zvolený čas ověří minutovou a hodinovou. Nehybné části se neotáčejí. Počet draw callů hodin zůstává jedna.

### 8. Závěrečné ověření

- Přeložit projekt v používané konfiguraci Visual Studia a spustit z obvyklé pracovní složky kvůli relativním cestám shaderů.
- Projít všechny scény, resize, přepínání, pohyb, podpis a ukončení aplikace.
- Ověřit okamžitou synchronizaci observerů a shodný pohled ve všech shaderech lesa.
- Ověřit nejméně 74 stromů a jediný draw call celých hodin.
- Připravit screenshoty a stručný popis: ovládání, vazba Camera → ShaderProgram přes Observer a řešení ručiček v shaderu. Způsob odevzdání potvrdit podle aktuálního portálu; v Kelvin/Zadání zatím není zadání CV5.

## Co nyní nepřidávat

Ortogonální projekce je ve CV5 nabízená k vyzkoušení, pro základní řešení ji nepotřebujeme. Stejně tak není potřeba Singleton, obecný event systém, hierarchie ovladačů kamer, kolize, instancing lesa, nové knihovny ani osvětlení z dalšího cvičení.

První společný krok bude dokončení deklarace a základního stavu v existujícím `camera.h`; k Observeru přejdeme až po vysvětlení a ověření samotné kamery.
