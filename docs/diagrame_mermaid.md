# Diagrame Mermaid - Lab 5

Acest fisier contine cod Mermaid pentru:
- Sarcina 1: control PID turatie motor (`app_lab_5_1`)
- Sarcina 2: control ON-OFF cu histereza pentru pozitie (`app_lab_5_2`)

## Sarcina 1 - PID turatie

### FSM

```mermaid
stateDiagram-v2
    [*] --> Init
    Init: setup serial + encoder + L298 + PID
    Init --> WaitSetPoint

    WaitSetPoint: asteapta valoare prin scanf
    WaitSetPoint --> ControlLoop: setpoint valid primit

    ControlLoop: citire RPM + PID + comanda PWM
    ControlLoop --> ControlLoop: CONTROL_PERIOD_MS
    ControlLoop --> Report: STATUS_PERIOD_MS

    Report: printf(SP, PV, OUT, PWM)
    Report --> ControlLoop
```

### FlowChart

```mermaid
flowchart TD
    A[Pornire MCU] --> B[ddSerialStdioSetup]
    B --> C[ddEncoderInit]
    C --> D[srvDcMotorInit]
    D --> E[srvPidInit]
    E --> F{Serial disponibil?}
    F -- Nu --> G[Verifica timer control]
    F -- Da --> H[scanf SetPoint]
    H --> G
    G --> I{A trecut CONTROL_PERIOD_MS?}
    I -- Nu --> J[Verifica timer status]
    I -- Da --> K[Citire RPM din encoder]
    K --> L[Calcul PID]
    L --> M[Limitare si mapare la 0..100%]
    M --> N[srvDcMotorSetPower]
    N --> J
    J --> O{A trecut STATUS_PERIOD_MS?}
    O -- Nu --> F
    O -- Da --> P[printf SP, PV, OUT, PWM]
    P --> F
```

## Sarcina 2 - ON-OFF cu histereza (pozitie rotor)

### FSM

```mermaid
stateDiagram-v2
    [*] --> Init
    Init: setup serial + encoder + L298
    Init --> Idle

    Idle: in banda de histereza\nmotor OFF
    Idle --> DriveFwd: PV < SP - H
    Idle --> DriveRev: PV > SP + H

    DriveFwd: motor +50%
    DriveFwd --> Idle: PV >= SP - H
    DriveFwd --> DriveRev: PV > SP + H

    DriveRev: motor -50%
    DriveRev --> Idle: PV <= SP + H
    DriveRev --> DriveFwd: PV < SP - H

    Idle --> Report: STATUS_PERIOD_MS
    DriveFwd --> Report: STATUS_PERIOD_MS
    DriveRev --> Report: STATUS_PERIOD_MS
    Report: printf(SP, PV, H, ST, PWM)
    Report --> Idle
```

### FlowChart

```mermaid
flowchart TD
    A[Pornire MCU] --> B[ddSerialStdioSetup]
    B --> C[ddEncoderInit + reset pozitie]
    C --> D[srvDcMotorInit]
    D --> E{Serial disponibil?}
    E -- Nu --> F[Citeste pozitia curenta PV]
    E -- Da --> G[scanf SetPoint ticks]
    G --> F

    F --> H[Calculeaza praguri: SP-H si SP+H]
    H --> I{PV < SP-H?}
    I -- Da --> J[Comanda ON_FWD la 50%]
    I -- Nu --> K{PV > SP+H?}
    K -- Da --> L[Comanda ON_REV la 50%]
    K -- Nu --> M[Comanda OFF]

    J --> N{A trecut STATUS_PERIOD_MS?}
    L --> N
    M --> N
    N -- Nu --> E
    N -- Da --> O[printf SP, PV, H, ST, PWM]
    O --> E
```
