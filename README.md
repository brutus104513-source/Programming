# ФизКат

ДЗ №2, C++17. Учёт транспорта и вещей.

## Запуск

Открыть терминал в папке Fleet. Для Windows с g++:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp Transport.cpp -o fleet.exe
.\fleet.exe
```

Для Linux/macOS: та же сборка с `-o fleet`, запуск `./fleet`.
После запуска вводить команды, для выхода — `quit`.

Команды из задания: `add`, `energy`, `novice`, `list`, `focus id`,
`show_focus`, `remove id`, `quit`. Успешное добавление ничего не печатает.
ID и имя вводятся одним словом, без пробелов. Энергия неотрицательна,
простота — целое от 1 до 10, ID не должен повторяться.

## Устройство

Базисы объявлены в [Inventory.hpp](Inventory.hpp), транспорт — в
[Transport.hpp](Transport.hpp), вещи — в [Things.hpp](Things.hpp).
Все связи наследования public:

| Класс | Базовые классы |
| --- | --- |
| StoredItem | InventoryItem |
| Transport | StoredItem |
| Bike, CargoBike | Transport |
| ElectricScooter, ElectricBike | Transport, EnergyConsumer |
| Helmet | StoredItem |
| DockStation | StoredItem, EnergyConsumer |

`InventoryItem` и `EnergyConsumer` абстрактные. У электротранспорта и
док-станции множественное наследование; ромба нет, virtual inheritance не нужен.
В [Fleet.hpp](Fleet.hpp) печать, энергия и отбор новичков работают через
виртуальные методы InventoryItem.

## Указатели, операторы и шаблоны

- `unique_ptr` в [Registry.hpp](Registry.hpp) обеспечивает единоличное владение позициями.
- `shared_ptr<const ModelSpec>` в [Transport.cpp](Transport.cpp) хранит общую спецификацию для объектов одного вида.
- `weak_ptr` в Fleet наблюдает карточку позиции, которой владеет StoredItem. После удаления позиции `show_focus` печатает `removed / expired`. Карточка позволяет не превращать владение самой позицией в shared_ptr.
- В Inventory.hpp: `<<` печатает позицию, `<` сравнивает ID, `==` проверяет совпадение ID при добавлении.
- `Registry<T>` — шаблонный журнал с add, size, operator[], erase и печатью. В парке используется `Registry<InventoryItem>`; шаблонная функция `sumEnergy` применяется в отчётах.

## Ошибки

В [Errors.hpp](Errors.hpp) общий базис FleetError наследуется от std::runtime_error.
`InspectionRejected` — отказ техосмотра, `InvalidArgument` — неверные аргументы
или повторный ID, `ItemNotFound` — отсутствующий ID.
[ServiceCenter.hpp](ServiceCenter.hpp) отклоняет транспорт, если имя содержит
`broken` без учёта регистра. Проверки проходят до добавления в парк.
Сообщения `error: ...` выводятся только в catch в [main.cpp](main.cpp).

## Дополнения

Добавлен CargoBike: `add cargo id name score capacityKg` — грузовой велосипед
с положительной целой грузоподъёмностью, без расхода энергии.
`count_novice` считает подходящий новичкам транспорт, `novice_threshold n`
меняет порог (изначально 6), `report` выводит число позиций и общую энергию.

## Использование ИИ

ИИ использовался при подготовке README.
