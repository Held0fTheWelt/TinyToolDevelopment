<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Referencia de configuración

LogLevelEditor almacena su configuración en `ULogLevelEditor_Settings`.

## Objeto de configuración

Archivo fuente:

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

Alcance de la configuración:

```text
EditorPerProjectUserSettings
```

Esto significa que muchos ajustes son propios del usuario o del editor en lugar de ajustes en tiempo de ejecución del juego.

## LogLevelDataAsset

Tipo:

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

Predeterminado:

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

Propósito:

- Almacena modificaciones persistentes de nivel de detalle por categoría.
- Se carga mediante el módulo al iniciar.
- Se actualiza mediante el widget tras ejecutar con éxito un comando.

Recomendación:

- Utilice el asset predeterminado proporcionado para proyectos pequeños.
- Cree una copia específica para el proyecto si desea una propiedad estricta en el control de código fuente.

## bAutoSaveLogLevelDataAsset

Predeterminado:

```text
true
```

Propósito:

- Guarda el DataAsset tras cambios en las modificaciones persistentes.
- Reduce el riesgo de que un usuario olvide guardar el DataAsset tras modificar la política de registro.

## bShowToolbarButton

Predeterminado:

```text
true
```

Propósito:

- Muestra el acceso directo a Log Level Editor en la barra de herramientas del Level Editor.
- La entrada del menú **Tools → Log Tools → Log Level Editor** permanece disponible aunque este acceso directo esté oculto.

## bAlsoListEnginePluginChannels

Predeterminado:

```text
false
```

Propósito:

- Incluye los directorios de código fuente de los plugins del motor en el escáner.

Compromiso:

- Resultados más completos.
- Mayor tiempo de escaneo y más categorías en la interfaz.

## bAlsoListEngineSourceChannels

Predeterminado:

```text
false
```

Propósito:

- Incluye los directorios de código fuente del motor en el escáner.

Compromiso:

- Visibilidad muy amplia.
- Escaneos potencialmente mucho más pesados.

## bTemporaryHideLogLevels

Predeterminado:

```text
false
```

Propósito:

- Activa la lista de ocultación de uso exclusivo en la sesión.

Almacenamiento:

- Volátil (Transient).
- No se guarda en la configuración.

## LogChannelsToHideTemporary

Propósito:

- Nombres de categorías ocultas únicamente durante la sesión actual del editor.

Ejemplo:

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

Propósito:

- Nombres de categorías ocultas entre sesiones.

Recomendación:

- Usar con moderación. La ocultación permanente puede dificultar el descubrimiento posterior de registros relevantes.

## Configuración base recomendada

Para la mayoría de los proyectos:

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```
