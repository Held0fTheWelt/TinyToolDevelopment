# Documentación de GameFeaturedClasses

GameFeaturedClasses es una cáscara de complemento de tiempo de ejecución ligera para clases de jugabilidad destacada específicas del proyecto. La versión `1.0.1` incluye el descriptor, metadatos de empaquetado, icono, registro de cambios y un límite de módulo de tiempo de ejecución (`StartupModule` / `ShutdownModule`).

Audiencia: equipos que necesitan el límite de paquete GFC en un proyecto hoy en día, mientras que las clases destacadas y el banco de trabajo premium GameFeature Workbench siguen siendo la arquitectura objetivo (aún no disponible en este paquete).

## Paquete actual

- El módulo de tiempo de ejecución `GameFeaturedClasses` se carga después de habilitar y reiniciar.
- Aún no se incluyen activos de clase de jugabilidad destacada, acciones de Game Feature, registro o banco de trabajo del editor.
- No se requiere ningún otro complemento de Tiny Tool para la cáscara.

## Primeros pasos

1. Habilita el complemento: consulta el ejemplo práctico en [QUICKSTART.md](QUICKSTART.md) (comprobación de humo del módulo).
2. Lee [UserManual.md](UserManual.md) para conocer el límite actual frente al objetivo.
3. Usa [TROUBLESHOOTING.md](TROUBLESHOOTING.md) cuando se espere un menú del banco de trabajo pero esté ausente.

## Archivos relacionados

- [../README.md](../README.md) — descripción general del producto.
- [../CHANGELOG.md](../CHANGELOG.md) — historial de lanzamientos.
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)
